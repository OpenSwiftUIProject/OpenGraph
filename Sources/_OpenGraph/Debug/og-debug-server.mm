//
//  og-debug-server.mm
//  OpenGraph
//
//  Created by Kyle on 2024/1/11.
//  Audited for 2021 Release

#include "og-debug-server.hpp"
#if TARGET_OS_DARWIN

#include "../Util/log.hpp"
#include "../Util/assert.hpp"
#include "../Graph/GraphDescription.hpp"
#include "../Graph/Graph.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <Foundation/Foundation.h>
#include <errno.h>
#include <assert.h>

// MARK: DebugServer Implementation

OG::DebugServer* _Nullable OG::DebugServer::_shared_server = nullptr;

OG::DebugServer* _Nullable OG::DebugServer::start(unsigned int mode) {
    bool validPort = mode & 1;
    if (OG::DebugServer::_shared_server == nullptr
        && validPort
        /*&& os_variant_has_internal_diagnostics("com.apple.AttributeGraph")*/
    ) {
        _shared_server = new DebugServer(mode);
    }
    return OG::DebugServer::_shared_server;
}

void OG::DebugServer::stop() {
    if (OG::DebugServer::_shared_server == nullptr) {
        return;
    }
    _shared_server->~DebugServer();
    delete _shared_server;
    _shared_server = nullptr;
}

OG::DebugServer::DebugServer(unsigned int mode) {
    sockfd = -1;
    ip = 0;
    port = 0;
    token = arc4random();
    source = nullptr;
    connections = OG::vector<std::unique_ptr<Connection>, 0, unsigned long>();
    
    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("OGDebugServer: socket");
        return;
    }
    
    // fcntl
    fcntl(sockfd, F_SETFD, O_WRONLY);
    
    // setsockopt
    const int value = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, &value, 4);
    
    // bind
    sockaddr_in addr = sockaddr_in();
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = ((mode & 2) == 0) ? htonl(INADDR_LOOPBACK) : 0;
    socklen_t slen = sizeof(sockaddr_in);
    if (bind(sockfd, (const sockaddr *)&addr, slen)) {
        perror("OGDebugServer: bind");
        shutdown();
        return;
    }
    
    // getsockname
    if (getsockname(sockfd, (sockaddr *)&addr, &slen)) {
        perror("OGDebugServer: getsockname");
        shutdown();
        return;
    }
    ip = ntohl(addr.sin_addr.s_addr);
    port = ntohl(addr.sin_port) >> 16;
    if (mode & 2) {
        ifaddrs *iaddrs = nullptr;
        if (getifaddrs(&iaddrs) == 0) {
            ifaddrs *current_iaddrs = iaddrs;
            while (current_iaddrs != nullptr) {
                sockaddr_in *ifa_addr = (sockaddr_in *)current_iaddrs->ifa_addr;
                if (ifa_addr != nullptr && ifa_addr->sin_family == AF_INET) {
                    uint32_t ip_data = ntohl(ifa_addr->sin_addr.s_addr);
                    if (ip_data != INADDR_LOOPBACK) {
                        ip = ip_data;
                    }
                }
                current_iaddrs = current_iaddrs->ifa_next;
            }
            freeifaddrs(iaddrs);
        }
    }
    
    // listen
    int max_connection_count = 5;
    if (listen(sockfd, max_connection_count)) {
        perror("OGDebugServer: listen");
        shutdown();
        return;
    }
    
    // Dispatch
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, sockfd, 0, dispatch_get_main_queue());
    dispatch_set_context(source, this);
    dispatch_source_set_event_handler_f(source, &accept_handler);
    dispatch_resume(source);
    
    // inet_ntop
    char address[32] = {0};
    inet_ntop(AF_INET, (const void *)(&addr.sin_addr.s_addr), address, 32);
    
    // log
    os_log_info(misc_log(), "debug server graph://%s:%d/?token=%u", address, port, token);
    fprintf(stderr, "debug server graph://%s:%d/?token=%u\\n", address, port, token);
}

// TODO: To be implemented
OG::DebugServer::~DebugServer() {}

// TODO: select will fail here
void OG::DebugServer::run(int timeout) {
    bool accepted_connection = false;
    
    while (true) {
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        timeval tv = timeval { timeout, 0 };
        
        if (select(sockfd+1, nullptr, &writefds, nullptr, &tv) <= 0) {
            if (errno == EAGAIN) {
                continue;
            } else {
                perror("OGDebugServer: select");
                return;
            }
        }
    }
}

void OG::DebugServer::accept_handler(void *_Nullable context) {
    DebugServer *server = (DebugServer *)context;
    sockaddr address;
    socklen_t address_len = 16;
    
    int sockfd = accept(server->sockfd, &address, &address_len);
    if (sockfd) {
        perror("OGDebugServer: accept");
        return;
    }
    fcntl(server->sockfd, F_SETFD, O_WRONLY);
    server->connections.push_back(std::unique_ptr<Connection>(new Connection(server, sockfd)));
}

CFURLRef _Nullable OG::DebugServer::copy_url() const {
    if (sockfd < 0) {
        return nullptr;
    }
    uint32_t converted_ip = htonl(ip);
    char address[32] = {0};
    inet_ntop(AF_INET, &converted_ip, address, 32);
    char url[100] = {0};
    snprintf_l(url, 0x100, nullptr, "graph://%s:%d/?token=%u", address, port, token);
    return CFURLCreateWithBytes(kCFAllocatorDefault, (const UInt8 *)url, strlen(url), kCFStringEncodingUTF8, nullptr);
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

// TODO: part implemented
CFDataRef _Nullable OG::DebugServer::receive(Connection *, OGDebugServerMessageHeader &, CFDataRef data) {
    @autoreleasepool {
        id object = [NSJSONSerialization JSONObjectWithData:(__bridge NSData *)data options:0 error:NULL];
        if (object && [object isKindOfClass:NSDictionary.class]) {
            NSDictionary *dic = (NSDictionary *)object;
            NSString *command = dic[@"command"];
            if ([command isEqual:@"graph/description"]) {
                NSMutableDictionary *mutableDic = [NSMutableDictionary dictionaryWithDictionary:dic];
                mutableDic[(__bridge NSString *)OGDescriptionFormat] = @"graph/dict";
                CFTypeRef description = OG::Graph::description(nullptr, mutableDic);
                if (description) {
                    NSData *descriptionData = [NSJSONSerialization dataWithJSONObject:(__bridge id)description options:0 error:NULL];
                    return (__bridge CFDataRef)descriptionData;
                }
            } else if ([command isEqual:@"profiler/start"]) {
                // TODO
            } else if ([command isEqual:@"profiler/stop"]) {
                // TODO
            } else if ([command isEqual:@"profiler/reset"]) {
                // TODO
            } else if ([command isEqual:@"profiler/mark"]) {
                // TODO
            }
        }
        return nullptr;
    }
}

void OG::DebugServer::close_connection(OG::DebugServer::Connection *connection) {
    auto it = connections.begin();
    for (; it != connections.end(); it++) {
        if (it->get() == connection) {
            connections.pop_back();
            return;
        }
    }
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

#endif /* TARGET_OS_DARWIN */
