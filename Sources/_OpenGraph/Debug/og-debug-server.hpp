//
//  og-debug-server.hpp
//
//
//  Created by Kyle on 2024/1/11.
//  Audited for 2021 Release

#ifndef og_debug_server_hpp
#define og_debug_server_hpp

#include <OpenFoundation/OpenFoundation.h>
#if TARGET_OS_DARWIN
#include <CoreFoundation/CoreFoundation.h>
#include <dispatch/dispatch.h>

OF_ASSUME_NONNULL_BEGIN

namespace OG {
class DebugServer {
private:
    int32_t fd;
    uint32_t ip;
    uint32_t port;
    uint32_t token;
    _Nullable dispatch_source_t source;
    _Nullable dispatch_source_t unknown;
public:
    static DebugServer *_Nullable _shared_server;
    static DebugServer *_Nullable start(unsigned int port);
    static void stop();
    DebugServer(unsigned int port);
    ~DebugServer();
    void run(int descriptor);
    static void accept_handler(void *_Nullable context);
    CFURLRef _Nullable copy_url() const;
    void shutdown();
    
    
    class Connection {
    private:
        DebugServer *server;
        int descriptor;
        dispatch_source_t source;
    public:
        Connection(DebugServer *server,int descriptor);
        ~Connection();
        static void handler(void *_Nullable context); // TODO
    };
};
}


// MARK: - Exported C functions

OF_EXTERN_C_BEGIN
OF_EXPORT
OG::DebugServer* _Nullable OGDebugServerStart(unsigned int port);
OF_EXPORT
void OGDebugServerStop();
OF_EXPORT
CFURLRef _Nullable OGDebugServerCopyURL();
OF_EXPORT
void OGDebugServerRun(int descriptor);
OF_EXTERN_C_END

OF_ASSUME_NONNULL_END

#endif /* TARGET_OS_DARWIN */
#endif /* og_debug_server_ hpp */
