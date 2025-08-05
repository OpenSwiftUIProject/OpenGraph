//
//  DebugServer.mm
//  OpenGraphCxx
//
//  Audited for 6.5.1
//  Status: Blocked by profile command

// TODO:
// 1. select will both fail on AG and OG with different error.
// 2. run(timeout)'s purpose? And update documentation for hpp and h
// 3. Implement profile commands.

#include <OpenGraphCxx/DebugServer/DebugServer.hpp>
#if OG_TARGET_OS_DARWIN

#include <OpenGraph/OGGraphDescription.h>
#include <OpenGraphCxx/Misc/log.hpp>
#include <OpenGraphCxx/Misc/assert.hpp>
#include <OpenGraphCxx/Graph/Graph.hpp>

#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <Foundation/Foundation.h>
#include <errno.h>
#include <assert.h>

OG_EXTERN_C_BEGIN
// DYLD_INTERPOSE does not work. Directly use the hook one here to match the semantics.
bool og_variant_has_internal_diagnostics(const char *subsystem);
OG_EXTERN_C_END

// MARK: DebugServer public API Implementation

OG::DebugServer::DebugServer(OGDebugServerMode mode) {
    sockfd = -1;
    ip = 0;
    port = 0;
    token = arc4random();
    source = nullptr;
    connections = OG::vector<std::unique_ptr<Connection>, 0, u_long>();

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("OGDebugServer: socket");
        return;
    }

    // Set socket options
    fcntl(sockfd, F_SETFD, FD_CLOEXEC);

    // setsockopt
    int value = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&value, sizeof(value));

    // Prepare address structure
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0; // Let system assign port
    addr.sin_addr.s_addr = (mode & OGDebugServerModeNetworkInterface) ? INADDR_ANY : htonl(INADDR_LOOPBACK);

    // Bind socket
    if (bind(sockfd, (const sockaddr *)&addr, sizeof(addr))) {
        perror("OGDebugServer: bind");
        shutdown();
        return;
    }

    // Get assigned address and port
    socklen_t slen = sizeof(addr);
    if (getsockname(sockfd, (sockaddr *)&addr, &slen)) {
        perror("OGDebugServer: getsockname");
        shutdown();
        return;
    }
    ip = ntohl(addr.sin_addr.s_addr);
    port = ntohs(addr.sin_port);

    // If network interface mode, find external IP
    if (mode & OGDebugServerModeNetworkInterface) {
        ifaddrs *iaddrs = nullptr;
        if (getifaddrs(&iaddrs) == 0) {
            ifaddrs *current_iaddrs = iaddrs;
            while (current_iaddrs != nullptr) {
                sockaddr_in *ifa_addr = (sockaddr_in *)current_iaddrs->ifa_addr;
                if (ifa_addr != nullptr && ifa_addr->sin_family == AF_INET) {
                    uint32_t ip_data = ntohl(ifa_addr->sin_addr.s_addr);
                    if (ip_data != INADDR_LOOPBACK) {
                        ip = ip_data;
                        break;  // Take first non-loopback interface
                    }
                }
                current_iaddrs = current_iaddrs->ifa_next;
            }
            freeifaddrs(iaddrs);
        }
    }

    // listen
    if (listen(sockfd, 5)) {
        perror("OGDebugServer: listen");
        shutdown();
        return;
    }

    // Set up dispatch source for incoming connections
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, sockfd, 0, dispatch_get_main_queue());
    dispatch_set_context(source, this);
    dispatch_source_set_event_handler_f(source, &accept_handler);
    dispatch_resume(source);

    // Log server information
    char address[32];
    uint32_t converted_ip = htonl(ip);
    inet_ntop(AF_INET, &converted_ip, address, sizeof(address));
    os_log(misc_log(), "debug server graph://%s:%d/?token=%u", address, port, token);
    fprintf(stderr, "debug server graph://%s:%d/?token=%u\n", address, port, token);
}

OG::DebugServer::DebugServer(DebugServer&& other) OG_NOEXCEPT
    : sockfd(other.sockfd)
    , ip(other.ip)
    , port(other.port)
    , token(other.token)
    , source(other.source)
    , connections(std::move(other.connections))
{
    other.sockfd = -1;
    other.ip = 0;
    other.port = 0;
    other.token = 0;
    other.source = nullptr;
}

OG::DebugServer& OG::DebugServer::operator=(DebugServer&& other) OG_NOEXCEPT {
    if (this != &other) {
        shutdown();
        for (auto &connection : connections) {
            connection.reset();
        }

        sockfd = other.sockfd;
        ip = other.ip;
        port = other.port;
        token = other.token;
        source = other.source;
        connections = std::move(other.connections);

        other.sockfd = -1;
        other.ip = 0;
        other.port = 0;
        other.token = 0;
        other.source = nullptr;
    }
    return *this;
}

OG::DebugServer::~DebugServer() {
    shutdown();
    for (auto &connection : connections) {
        connection.reset();
    }
}

CFURLRef _Nullable OG::DebugServer::copy_url() const {
    if (sockfd < 0) {
        return nullptr;
    }
    uint32_t converted_ip = htonl(ip);
    char address[32];
    inet_ntop(AF_INET, &converted_ip, address, 32);
    char url[100];
    snprintf_l(url, 0x100, nullptr, "graph://%s:%d/?token=%u", address, port, token);
    return CFURLCreateWithBytes(NULL, (const UInt8 *)url, strlen(url), kCFStringEncodingUTF8, nullptr);
}

// NOTE: Copilot implementation
void OG::DebugServer::run(int timeout) const {
    bool accepted_connection = false;
    
    while (true) {
        // Early exit condition check
        if (accepted_connection && connections.size() == 0) {
            break;
        }
        
        // Initialize the fd_set for write operations
        fd_set writefds;
        FD_ZERO(&writefds);
        
        // Add the server socket to the fd_set
        int server_fd = sockfd;
        FD_SET(server_fd, &writefds);
        
        // Find the maximum file descriptor and add all connection sockets
        int max_fd = server_fd;
        size_t connection_count = connections.size();
        
        if (connection_count > 0) {
            auto connection_data = connections.data();
            for (size_t i = 0; i < connection_count; ++i) {
                int conn_fd = connection_data[i]->sockfd;
                FD_SET(conn_fd, &writefds);
                if (max_fd < conn_fd) {
                    max_fd = conn_fd;
                }
            }
        }
        
        // Set up timeout
        timeval tv = {timeout, 0};
        
        // Call select with write file descriptors
        int select_result = select(max_fd + 1, nullptr, &writefds, nullptr, &tv);
        if (select_result <= 0) {
            if (errno == EAGAIN) {
                // Continue the loop on EAGAIN
                continue;
            }
            perror("OGDebugServer: select");
            return;
        }

        // Check if server socket is ready for new connections
        if (FD_ISSET(server_fd, &writefds)) {
            accept_handler((void *)this);
            accepted_connection = true;
        }
        
        // Process ready connection sockets
        if (connections.size() > 0) {
            size_t i = 0;
            while (i < connections.size()) {
                auto connection = connections.data()[i].get();
                int conn_fd = connection->sockfd;
                
                if (FD_ISSET(conn_fd, &writefds)) {
                    
                    // Clear the FD from the set before processing
                    FD_CLR(conn_fd, &writefds);
                    
                    // Handle the connection
                    Connection::handler(connection);
                    
                    // Reset index to 0 after handling a connection
                    // (connection might have been removed)
                    i = 0;
                } else {
                    i++;
                }
                
                // Break if no more connections
                if (connections.size() == 0) {
                    break;
                }
            }
        }
    }
}
OG::DebugServer* _Nullable OG::DebugServer::start(OGDebugServerMode mode) {
    if (
        (mode & OGDebugServerModeValid)
        && !OG::DebugServer::has_shared_server()
        && og_variant_has_internal_diagnostics("org.OpenSwiftUIProject.OpenGraph")
    ) {
        _shared_server = new DebugServer(mode);
    }
    return OG::DebugServer::_shared_server;
}

void OG::DebugServer::stop() {
    if (!OG::DebugServer::has_shared_server()) {
        return;
    }
    delete _shared_server;
    _shared_server = nullptr;
}

// MARK: Blocking operation

namespace OG {
namespace {
bool blocking_read(int descriptor, void *buf, unsigned long count) {
    ssize_t offset = 0;
    while (offset < count) {
        ssize_t read_count = read(descriptor, (void *)((char *)buf+offset), count+offset);
        if (read_count == 0) {
            return false;
        } else if (read_count < 0) {
            if (errno != EINTR) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    perror("OGDebugServer: read");
                    return false;
                }
                assert("errno != EAGAIN && errno != EWOULDBLOCK");
            }
        } else {
            offset += read_count;
        }
    }
    return true;
}

bool blocking_write(int descriptor, void *buf, unsigned long count) {
    ssize_t offset = 0;
    while (offset < count) {
        ssize_t write_count = write(descriptor, (void *)((char *)buf+offset), count+offset);
        if (write_count == 0) {
            return false;
        } else if (write_count < 0) {
            if (errno != EINTR) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    perror("OGDebugServer: write");
                    return false;
                }
                assert("errno != EAGAIN && errno != EWOULDBLOCK");
            }
        } else {
            offset += write_count;
        }
    }
    return true;
}
} /* anonymous namespace */
} /* OG */

// MARK: Connection Implementation

OG::DebugServer::Connection::Connection(DebugServer *s,int d) {
    server = s;
    sockfd = d;
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, sockfd, 0, dispatch_get_main_queue());
    dispatch_set_context(source, this);
    dispatch_source_set_event_handler_f(source, &handler);
    dispatch_resume(source);
}

OG::DebugServer::Connection::~Connection() {
    dispatch_source_set_event_handler_f(source, nullptr);
    dispatch_set_context(source, nullptr);
    close(sockfd);
}

void OG::DebugServer::Connection::handler(void *_Nullable context) {
    Connection *connection = (Connection *)context;
    char buf[16] = {};
    if (blocking_read(connection->sockfd, &buf, 16)) {
        OGDebugServerMessageHeader *header = (OGDebugServerMessageHeader *)buf;
        header->unknown2 = 0;
        if (header->token == connection->server->token) {
            CFIndex length = header->length;
            CFMutableDataRef data = CFDataCreateMutable(kCFAllocatorDefault, length);
            if (data) {
                CFDataSetLength(data, length);
                UInt8 *data_ptr = CFDataGetMutableBytePtr(data);
                if (blocking_read(connection->sockfd, (void *)data_ptr, length)) {
                    CFDataRef receive_data = connection->server->receive(connection, *header, data);
                    if (receive_data) {
                        CFIndex receive_length = CFDataGetLength(receive_data);
                        header->length = (uint32_t)receive_length;
                        if ((receive_length >> 32) == 0) {
                            if(blocking_write(connection->sockfd, buf, 16)) {
                                const UInt8 *received_data_ptr = CFDataGetBytePtr(receive_data);
                                if(blocking_write(connection->sockfd, (void *)received_data_ptr, receive_length)) {
                                    connection = nullptr;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (connection) {
        connection->server->close_connection(connection);
    }
    return;
}

// MARK: DebugServer private API Implementation

// TODO: part implemented
CFDataRef _Nullable OG::DebugServer::receive(Connection *, OGDebugServerMessageHeader &, CFDataRef data) {
    @autoreleasepool {
        id object = [NSJSONSerialization JSONObjectWithData:(__bridge NSData *)data options:0 error:NULL];
        if (object && [object isKindOfClass:NSDictionary.class]) {
            NSDictionary *dic = (NSDictionary *)object;
            NSString *command = dic[@"command"];
            if ([command isEqual:@"graph/description"]) {
                NSMutableDictionary *mutableDic = [NSMutableDictionary dictionaryWithDictionary:dic];
                mutableDic[(__bridge NSString *)OGDescriptionFormat] = (__bridge NSString *)OGDescriptionFormatDictionary;
                CFTypeRef description = OG::Graph::description(nullptr, mutableDic);
                if (description) {
                    NSData *descriptionData = [NSJSONSerialization dataWithJSONObject:(__bridge id)description options:0 error:NULL];
                    return (__bridge CFDataRef)descriptionData;
                }
            } else if ([command isEqual:@"profiler/start"]) {
                // FIXME: Simply return the command str for now
                CFStringRef string = CFSTR("profiler/start");
                CFDataRef data = CFDataCreate(kCFAllocatorDefault, (const UInt8 *)CFStringGetCStringPtr(string, kCFStringEncodingUTF8), CFStringGetLength(string));
                CFRelease(string);
                return data;
            } else if ([command isEqual:@"profiler/stop"]) {
                // FIXME: Simply return the command str for now
                CFStringRef string = CFSTR("profiler/stop");
                CFDataRef data = CFDataCreate(kCFAllocatorDefault, (const UInt8 *)CFStringGetCStringPtr(string, kCFStringEncodingUTF8), CFStringGetLength(string));
                CFRelease(string);
                return data;
            } else if ([command isEqual:@"profiler/reset"]) {
                // FIXME: Simply return the command str for now
                CFStringRef string = CFSTR("profiler/reset");
                CFDataRef data = CFDataCreate(kCFAllocatorDefault, (const UInt8 *)CFStringGetCStringPtr(string, kCFStringEncodingUTF8), CFStringGetLength(string));
                CFRelease(string);
                return data;
            } else if ([command isEqual:@"profiler/mark"]) {
                // FIXME: Simply return the command str for now
                CFStringRef string = CFSTR("profiler/mark");
                CFDataRef data = CFDataCreate(kCFAllocatorDefault, (const UInt8 *)CFStringGetCStringPtr(string, kCFStringEncodingUTF8), CFStringGetLength(string));
                CFRelease(string);
                return data;
            }
        }
        return nullptr;
    }
}

void OG::DebugServer::close_connection(OG::DebugServer::Connection *target) {
    auto size = connections.size();
    if (size == 0) {
        return;
    }
    auto data = connections.data();
    for (size_t i = 0; i < size; ++i) {
        auto conn = data[i].get();
        if (conn == target) {
            // FIXME
            data[i] = std::move(data[size - 1]);
            connections.pop_back();
            return;
        }
    }
}

void OG::DebugServer::shutdown() {
    if (source != nullptr) {
        dispatch_source_set_event_handler_f(source, nullptr);
        dispatch_set_context(source, nullptr);
        source = nullptr;
    }
    if (sockfd >= 0) {
        close(sockfd);
        sockfd = -1;
    }
}

void OG::DebugServer::accept_handler(void *_Nullable context) {
    DebugServer *server = (DebugServer *)context;
    sockaddr address;
    socklen_t address_len = 16;
    int sockfd = accept(server->sockfd, &address, &address_len);
    if (sockfd < 0) {
        perror("OGDebugServer: accept");
        return;
    }
    fcntl(server->sockfd, F_SETFD, O_WRONLY);
    server->connections.push_back(std::unique_ptr<Connection>(new Connection(server, sockfd)));
}

OG::DebugServer* _Nullable OG::DebugServer::_shared_server = nullptr;

#endif /* OG_TARGET_OS_DARWIN */
