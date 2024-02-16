//
//  OGDebugServer.hpp
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef OGDebugServer_hpp
#define OGDebugServer_hpp

#include "OGBase.hpp"

typedef struct OG_BRIDGED_TYPE(id) OGDebugServerStorage * OGDebugServerRef;

struct OGDebugServerStorage;

#if TARGET_OS_DARWIN

OG_ASSUME_NONNULL_BEGIN

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN
OG_EXPORT
OGDebugServerRef _Nullable OGDebugServerStart(unsigned int mode) OG_SWIFT_NAME(OGDebugServer.start(mode:));
OG_EXPORT
void OGDebugServerStop(void) OG_SWIFT_NAME(OGDebugServer.stop());
OG_EXPORT
CFURLRef _Nullable OGDebugServerCopyURL(void) OG_SWIFT_NAME(OGDebugServer.copyURL());
OG_EXPORT
void OGDebugServerRun(int timeout) OG_SWIFT_NAME(OGDebugServer.run(timeout:));
OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif

#endif /* OGDebugServer_hpp */
