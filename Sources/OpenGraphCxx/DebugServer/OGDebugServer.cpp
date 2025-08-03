//
//  OGDebugServer.cpp
//  OpenGraphCxx

#include <OpenGraph/OGDebugServer.h>
#include <OpenGraphCxx/DebugServer/DebugServer.hpp>

#if OG_TARGET_OS_DARWIN

// MARK: - Exported C functions

OGDebugServerRef _Nullable OGDebugServerStart(OGDebugServerMode port) {
    return (OGDebugServerRef)OG::DebugServer::start(port);
}

void OGDebugServerStop() {
    OG::DebugServer::stop();
}

CFURLRef _Nullable OGDebugServerCopyURL() {
    if (!OG::DebugServer::has_shared_server()) {
        return nullptr;
    }
    return OG::DebugServer::shared_server()->copy_url();
}

void OGDebugServerRun(int timeout) {
    if (!OG::DebugServer::has_shared_server()) {
        return;
    }
    OG::DebugServer::shared_server()->run(timeout);
}

#endif
