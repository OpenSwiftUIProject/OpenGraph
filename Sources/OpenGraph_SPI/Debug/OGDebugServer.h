//
//  OGDebugServer.h
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef OGDebugServer_h
#define OGDebugServer_h

#include "OGBase.h"

#if OG_TARGET_OS_DARWIN

OG_ASSUME_NONNULL_BEGIN

typedef struct OGDebugServerStorage OGDebugServerStorage;

typedef const OGDebugServerStorage *OGDebugServer OG_SWIFT_STRUCT;

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN
OG_EXPORT
OGDebugServer _Nullable OGDebugServerStart(unsigned int mode) OG_SWIFT_NAME(OGDebugServer.start(mode:));
OG_EXPORT
void OGDebugServerStop(void) OG_SWIFT_NAME(OGDebugServer.stop());
OG_EXPORT
CFURLRef _Nullable OGDebugServerCopyURL(void) OG_SWIFT_NAME(OGDebugServer.copyURL());
OG_EXPORT
void OGDebugServerRun(int timeout) OG_SWIFT_NAME(OGDebugServer.run(timeout:));
OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif

#endif /* OGDebugServer_h */
