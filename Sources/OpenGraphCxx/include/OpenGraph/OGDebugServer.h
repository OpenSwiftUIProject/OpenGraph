//
//  OGDebugServer.h
//  OpenGraphCxx
//
//  Audited for 6.5.1
//  Status: Complete

#ifndef OGDebugServer_h
#define OGDebugServer_h

#include <OpenGraph/OGBase.h>

#if OG_TARGET_OS_DARWIN

/**
 * @header OGDebugServer.h
 * @abstract OpenGraph Debug Server API for runtime debugging and inspection.
 * @discussion The debug server provides runtime debugging capabilities for OpenGraph applications,
 * allowing external tools to connect and inspect graph state, dependencies, and execution.
 * This API is only available on Darwin platforms and requires network interface access
 * when used in network mode.
 */

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

/**
 * @typedef OGDebugServerRef
 * @abstract An opaque reference to a debug server instance.
 * @discussion The debug server manages a connection endpoint that external debugging tools
 * can use to inspect OpenGraph runtime state. Only one debug server instance
 * can be active at a time.
 */
typedef struct OGDebugServerStorage *OGDebugServerRef OG_SWIFT_STRUCT OG_SWIFT_NAME(DebugServer);

/**
 * @typedef OGDebugServerMode
 * @abstract Configuration modes for the debug server.
 * @discussion These flags control how the debug server operates and what interfaces it exposes.
 * Multiple modes can be combined using bitwise OR operations.
 */
typedef OG_OPTIONS(uint32_t, OGDebugServerMode) {
    /**
     * @abstract No debug server functionality.
     * @discussion Use this mode to disable all debug server operations.
     */
    OGDebugServerModeNone = 0,
    
    /**
     * @abstract Enable basic debug server validation and setup.
     * @discussion This mode enables the debug server with minimal functionality and is required 
     * for any debug server operation. All other modes must be combined with this flag.
     */
    OGDebugServerModeValid = 1 << 0,
    
    /**
     * @abstract Enable network interface for remote debugging.
     * @discussion When enabled, the debug server will listen on a network interface, allowing 
     * remote debugging tools to connect. Requires OGDebugServerModeValid to be set.
     */
    OGDebugServerModeNetworkInterface = 1 << 1,
} OG_SWIFT_NAME(OGDebugServerRef.Mode);

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

/**
 * @function OGDebugServerStart
 * @abstract Starts the shared debug server with the specified mode.
 * @discussion Creates and starts a new shared debug server instance. If a server is already
 * running, this function will return the existing instance.
 * 
 * The returned reference should not be manually managed. Use OGDebugServerStop()
 * to properly shut down the shared server.
 * @param mode Configuration flags controlling server behavior.
 *             Must include OGDebugServerModeValid for basic operation.
 * @result A reference to the started shared debug server, or NULL if the server
 *         could not be started (e.g., due to network permissions, conflicts, or existing server).
 */
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGDebugServerRef _Nullable OGDebugServerStart(OGDebugServerMode mode) OG_SWIFT_NAME(OGDebugServerRef.start(mode:));

/**
 * @function OGDebugServerStop
 * @abstract Stops and deletes the running shared debug server.
 * @discussion Shuts down the active shared debug server instance and cleans up all associated
 * resources. If no shared debug server is currently running, this function has no effect.
 * 
 * This function should be called before application termination to ensure
 * proper cleanup of network resources and connections.
 */
OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGDebugServerStop(void) OG_SWIFT_NAME(OGDebugServerRef.stop());

/**
 * @function OGDebugServerCopyURL
 * @abstract Returns the URL for connecting to the shared debug server.
 * @discussion Returns the URL that external debugging tools should use to connect to
 * the currently running shared debug server. The URL format depends on the server
 * configuration and may be a local or network address.
 * 
 * The returned URL is only valid while the shared debug server is running.
 * It may change if the server is restarted.
 * @result A CFURLRef containing the connection URL, or NULL if no shared debug server
 *         is currently running or if the server doesn't expose a connectable interface.
 *         The caller is responsible for releasing the returned URL.
 */
OG_EXPORT
OG_REFINED_FOR_SWIFT
CFURLRef _Nullable OGDebugServerCopyURL(void) OG_SWIFT_NAME(OGDebugServerRef.copyURL());

/**
 * @function OGDebugServerRun
 * @abstract Runs the shared debug server event loop.
 */
OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGDebugServerRun(int timeout) OG_SWIFT_NAME(OGDebugServerRef.run(timeout:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif

#endif /* OGDebugServer_h */
