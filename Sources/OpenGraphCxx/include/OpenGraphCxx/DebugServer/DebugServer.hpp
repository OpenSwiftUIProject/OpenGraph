//
//  DebugServer.hpp
//  OpenGraphCxx
//
//  Audited for 6.5.1
//  Status: Complete

#ifndef OPENGRAPH_CXX_DEBUGSERVER_DEBUGSERVER_HPP
#define OPENGRAPH_CXX_DEBUGSERVER_DEBUGSERVER_HPP

#include <OpenGraph/OGBase.h>
#if OG_TARGET_OS_DARWIN
#include <OpenGraph/OGDebugServer.h>
#include <OpenGraphCxx/Vector/vector.hpp>
#include <dispatch/dispatch.h>
#include <memory>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

namespace OG {
struct OGDebugServerMessageHeader {
    uint32_t token;
    uint32_t unknown;
    uint32_t length;
    uint32_t unknown2;
}; /* OGDebugServerMessageHeader */

class DebugServer {
public:
    DebugServer(OGDebugServerMode mode);
    ~DebugServer();

    CFURLRef _Nullable copy_url() const;
    void run(int descriptor);

    static OG_INLINE DebugServer *shared_server() { return _shared_server; }
    static OG_INLINE bool has_shared_server() { return _shared_server != nullptr; }

    static DebugServer *_Nullable start(unsigned int port);
    static void stop();

private:
    class Connection {
    public:
        Connection(DebugServer *server,int descriptor);
        ~Connection();

        static void handler(void *_Nullable context);

        friend class DebugServer;
    private:
        DebugServer *server;
        int sockfd;
        dispatch_source_t source;
    }; /* Connection */

    CFDataRef _Nullable receive(Connection *connection, OGDebugServerMessageHeader &header, CFDataRef data);
    void close_connection(Connection *connection);
    void shutdown();

    static void accept_handler(void *_Nullable context);

    int32_t sockfd;
    uint32_t ip;
    uint32_t port;
    uint32_t token;
    _Nullable dispatch_source_t source;
    OG::vector<std::unique_ptr<Connection>, 0, u_long> connections;

    static DebugServer *_Nullable _shared_server;
}; /* DebugServer */

} /* OG */

typedef struct OGDebugServerStorage {
    OG::DebugServer debugServer;
} OGDebugServerStorage;

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OG_TARGET_OS_DARWIN */
#endif /* OPENGRAPH_CXX_DEBUGSERVER_DEBUGSERVER_HPP */
