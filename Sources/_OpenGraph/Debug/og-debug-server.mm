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
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <CoreFoundation/CoreFoundation.h>

OG::DebugServer* _Nullable OG::DebugServer::_shared_server = nullptr;

OG::DebugServer* _Nullable OG::DebugServer::start(unsigned int port) {
    bool validPort = port & 1;
    if (OG::DebugServer::_shared_server == nullptr
        && validPort
        /*&& os_variant_has_internal_diagnostics("com.apple.AttributeGraph")*/
    ) {
        _shared_server = new DebugServer(port);
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

OG::DebugServer::DebugServer(unsigned int p) {
    fd = -1;
    ip = 0;
    port = 0;
    token = arc4random();
    source = nullptr;
    unknown = nullptr;

    fd = socket(AF_INET, SOCK_STREAM, 0x0);
    if (fd < 0) {
        perror("OGDebugServer: socket");
        return;
    }
    fcntl(fd, F_SETFD, O_WRONLY);
    
    const int value = 1;
    setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &value, 4);
    
    sockaddr addr = sockaddr();
    addr.sa_family = AF_INET;
    addr.sa_data[0] = 0;
    addr.sa_data[1] = 0;
    u_int32_t sa_data = ((p & 2) == 0) ? htonl(INADDR_LOOPBACK) : 0;
    for (int i = 0; i < 4; i++) {
        addr.sa_data[2+i] = sa_data >> (i * 8);
    }
    
    if (bind(fd, &addr, 16)) {
        perror("OGDebugServer: bind");
        shutdown();
        return;
    }
    
    socklen_t length = 16;
    if (getsockname(fd, &addr, &length)) {
        perror("OGDebugServer: getsockname");
        shutdown();
        return;
    }
    
    u_int32_t ip_data = 0;
    for (int i = 0; i < 4; i++) {
        ip_data += addr.sa_data[2+i] << (i * 8);
    }
    ip_data = ntohl(ip_data);
    ip = ip_data;
    
    u_int32_t port_data = 0;
    for (int i = 0; i < 2; i++) {
        port_data += addr.sa_data[i] << (i * 8);
    }
    port_data = ntohl(port_data);
    port = port_data >> 16;
    
    if (p & 2) {
        ifaddrs *iaddrs = nullptr;
        if (getifaddrs(&iaddrs) == 0) {
            ifaddrs *current_iaddrs = iaddrs;
            while (current_iaddrs != nullptr) {
                auto *ifa_addr = current_iaddrs->ifa_addr;
                if (ifa_addr != nullptr && ifa_addr->sa_family == AF_INET) {
                    u_int32_t ip_data = 0;
                    for (int i = 0; i < 4; i++) {
                        ip_data += ifa_addr->sa_data[2+i] << (i * 8);
                    }
                    ip_data = ntohl(ip_data);
                    if (ip_data != INADDR_LOOPBACK) {
                        ip = ip_data;
                    }
                }
                current_iaddrs = current_iaddrs->ifa_next;
            }
            freeifaddrs(iaddrs);
        }
    }
    if (listen(fd, 5)) {
        perror("AGDebugServer: listen");
        shutdown();
        return;
    }
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, fd, 0, dispatch_get_main_queue());
    dispatch_set_context(source, this);
    dispatch_source_set_event_handler_f(source, &accept_handler);
    dispatch_resume(source);
    
    char address[32] = {0};
    inet_ntop(AF_INET, (void *)(&addr.sa_data[2]), address, 32);
    os_log_info(misc_log(), "debug server graph://%s:%d/?token=%u", address, port, token);
    fprintf(stderr, "debug server graph://%s:%d/?token=%u\\n", address, port, token);
}

OG::DebugServer::~DebugServer() {
    // TODO
}

void OG::DebugServer::run(int descriptor) {
    // TODO
}

void OG::DebugServer::accept_handler(void *_Nullable context) {
    DebugServer *server = (DebugServer *)context;
    sockaddr address;
    socklen_t address_len = 16;
    
    int descriptor = accept(server->fd, &address, &address_len);
    if (descriptor) {
        perror("OGDebugServer: accept");
        return;
    }
    fcntl(server->fd, F_SETFD, O_WRONLY);
    
    Connection *connection = new Connection(server, descriptor);
    // TODO
}

CFURLRef _Nullable OG::DebugServer::copy_url() const {
    if (fd < 0) {
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
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
}

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
    // TODO
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

void OGDebugServerRun(int descriptor) {
    if (OG::DebugServer::_shared_server == nullptr) {
        return;
    }
    OG::DebugServer::_shared_server->run(descriptor);
}

#endif /* TARGET_OS_DARWIN */
