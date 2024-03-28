//
//  AGDebugServer.h
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef AGDebugServer_h
#define AGDebugServer_h

#include "AGBase.h"

#if TARGET_OS_DARWIN

AG_ASSUME_NONNULL_BEGIN

typedef struct AGDebugServerStorage AGDebugServerStorage;

typedef const AGDebugServerStorage *AGDebugServer AG_SWIFT_STRUCT;

// MARK: - Exported C functions

AG_EXTERN_C_BEGIN
AG_EXPORT
AGDebugServer _Nullable AGDebugServerStart(unsigned int mode) AG_SWIFT_NAME(AGDebugServer.start(mode:));
AG_EXPORT
void AGDebugServerStop(void) AG_SWIFT_NAME(AGDebugServer.stop());
AG_EXPORT
CFURLRef _Nullable AGDebugServerCopyURL(void) AG_SWIFT_NAME(AGDebugServer.copyURL());
AG_EXPORT
void AGDebugServerRun(int timeout) AG_SWIFT_NAME(AGDebugServer.run(timeout:));
AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif

#endif /* AGDebugServer_h */
