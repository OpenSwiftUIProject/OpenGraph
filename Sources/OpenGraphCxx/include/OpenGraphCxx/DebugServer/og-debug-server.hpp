//
//  og-debug-server.hpp
//
//
//  Created by Kyle on 2024/1/11.
//  Audited for 2021 Release

#ifndef og_debug_server_hpp
#define og_debug_server_hpp

#include "OGBase.h"
#if OG_TARGET_OS_DARWIN
#include "OGDebugServer.h"
#include <OpenGraphCxx/Vector/vector.hpp>
#include <dispatch/dispatch.h>
#include <memory>

OG_ASSUME_NONNULL_BEGIN

namespace OG {
struct OGDebugServerMessageHeader {
    uint32_t token;
    uint32_t unknown;
    uint32_t length;
    uint32_t unknown2;
};
class DebugServer {
    class Connection {
    private:
        DebugServer *server;
        int sockfd;
        dispatch_source_t source;
    public:
        Connection(DebugServer *server,int descriptor);
        ~Connection();
        static void handler(void *_Nullable context);
        friend class DebugServer;
    };
private:
    int32_t sockfd;
    uint32_t ip;
    uint32_t port;
    uint32_t token;
    _Nullable dispatch_source_t source;
    OG::vector<std::unique_ptr<Connection>, 0, unsigned long> connections;
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
    CFDataRef _Nullable receive(Connection *connection, OGDebugServerMessageHeader &header, CFDataRef data);
    void close_connection(Connection *connection);
};
} /* OG */

typedef struct OGDebugServerStorage {
    OG::DebugServer debugServer;
} OGDebugServerStorage;


OG_ASSUME_NONNULL_END

#endif /* OG_TARGET_OS_DARWIN */
#endif /* og_debug_server_hpp */
