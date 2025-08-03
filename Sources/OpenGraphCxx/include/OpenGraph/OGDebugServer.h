//
//  OGDebugServer.h
//  OpenGraphCxx

#ifndef OGDebugServer_h
#define OGDebugServer_h

#include <OpenGraph/OGBase.h>

#if OG_TARGET_OS_DARWIN

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

typedef struct OG_BRIDGED_TYPE(id) OGDebugServerStorage * OGDebugServerRef OG_SWIFT_NAME(DebugServer);

typedef OG_OPTIONS(uint32_t, OGDebugServerMode) {
    OGDebugServerModeNone = 0,
    OGDebugServerModeValid = 1 << 0,
    OGDebugServerModeNetworkInterface = 1 << 1,
} OG_SWIFT_NAME(OGDebugServerRef.Mode);

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OGDebugServerRef _Nullable OGDebugServerStart(OGDebugServerMode mode) OG_SWIFT_NAME(OGDebugServerRef.start(mode:));

OG_EXPORT
void OGDebugServerStop(void) OG_SWIFT_NAME(OGDebugServerRef.stop());

OG_EXPORT
CFURLRef _Nullable OGDebugServerCopyURL(void) OG_SWIFT_NAME(OGDebugServerRef.copyURL());

OG_EXPORT
void OGDebugServerRun(int timeout) OG_SWIFT_NAME(OGDebugServerRef.run(timeout:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif

#endif /* OGDebugServer_h */
