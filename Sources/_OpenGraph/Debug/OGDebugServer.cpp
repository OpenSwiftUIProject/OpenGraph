//
//  OGDebugServer.cpp
//  
//
//  Created by Kyle on 2024/2/17.
//

#include "OGDebugServer.h"
#include "og-debug-server.hpp"

#if TARGET_OS_DARWIN

// MARK: - Exported C functions

OGDebugServerRef _Nullable OGDebugServerStart(unsigned int port) {
    return (OGDebugServerRef)OG::DebugServer::start(port);
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

#endif
