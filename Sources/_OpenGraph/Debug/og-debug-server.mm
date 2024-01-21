//
//  og-debug-server.mm
//  OpenGraph
//
//  Created by Kyle on 2024/1/11.
//  Audited for 2021 Release

#include "og-debug-server.hpp"
#if TARGET_OS_DARWIN

#include "OGLog.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/NSJSONSerialization.h>
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

OG::DebugServer::~DebugServer() {}

void OG::DebugServer::run(int timeout) {
    fd_set set = {};
    __darwin_fd_set(sockfd, &set);
    
    int descriptor = sockfd;
//    if (count != 0) {
//        __darwin_fd_set(connections[0]->descriptor, &set);
//    }
//    FD_ZERO();
//    FD_SET();
    timeval tv = timeval { timeout, 0 };
    select(descriptor+1, nullptr, &set, nullptr, &tv);
    int a = errno;
    std::cout << a;
}

void OG::DebugServer::accept_handler(void *_Nullable context) {
    DebugServer *server = (DebugServer *)context;
    sockaddr address;
    socklen_t address_len = 16;
    
    int descriptor = accept(server->sockfd, &address, &address_len);
    if (descriptor) {
        perror("OGDebugServer: accept");
        return;
    }
    fcntl(server->sockfd, F_SETFD, O_WRONLY);
    server->connections.push_back(std::unique_ptr<Connection>(new Connection(server, descriptor)));
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

__CFData *_Nullable OG::DebugServer::receive(Connection *connection, OGDebugServerMessageHeader &header, __CFData *data) {
    id jsonObject = [NSJSONSerialization JSONObjectWithData:(__bridge NSData *)data options:0 error:NULL];
    // TODO
    return nullptr;
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
}
}

// MARK: Connection Implementation

OG::DebugServer::Connection::Connection(DebugServer *s,int d) {
    server = s;
    descriptor = d;
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, descriptor, 0, dispatch_get_main_queue());
    dispatch_set_context(source, this);
    dispatch_source_set_event_handler_f(source, &handler);
    dispatch_resume(source);
}

OG::DebugServer::Connection::~Connection() {
    dispatch_source_set_event_handler_f(source, nullptr);
    dispatch_set_context(source, nullptr);
    close(descriptor);
}

void OG::DebugServer::Connection::handler(void *_Nullable context) {
    Connection *connection = (Connection *)context;
    char buf[16] = {};
    if (blocking_read(connection->descriptor, &buf, 16)) {
        uint32_t token = 0;
        for (int i = 0; i < 4; i++) {
            token += buf[i] << (i * 8);
            buf[12+i] = 0;
        }
        if (token == connection->server->token) {
            CFIndex length = 0;
            for (int i = 0; i < 4; i++) {
                length += buf[8+i] << (i * 8);
            }
            CFMutableDataRef data = CFDataCreateMutable(kCFAllocatorDefault, length);
            if (data) {
                CFDataSetLength(data, length);
                void *dataPtr = CFDataGetMutableBytePtr(data);
                if (blocking_read(connection->descriptor, dataPtr, length)) {
                    __CFData *receive_data = connection->server->receive(connection, (OGDebugServerMessageHeader &)buf, data);
                    if (receive_data) {
                        // TODO
                        // block_write
                    }
                }
            }
        }
    }
    connection->server->close_connection(connection);
    return;
}

// MARK: - Exported C functions

OG::DebugServer* _Nullable OGDebugServerStart(unsigned int port) {
    return OG::DebugServer::start(port);
}

void OGDebugServerStop() {
    OG::DebugServer::stop();
}

CFURLRef _Nullable OGDebugServerCopyURL() {
    if (OG::DebugServer::_shared_server == nullptr) {
        return nullptr;
    }
    return OG::DebugServer::_shared_server->copy_url();
}

void OGDebugServerRun(int timeout) {
    if (OG::DebugServer::_shared_server == nullptr) {
        return;
    }
    OG::DebugServer::_shared_server->run(timeout);
}

#endif /* TARGET_OS_DARWIN */
