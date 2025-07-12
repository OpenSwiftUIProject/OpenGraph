//
//  OGClosure.h
//  OpenGraphCxx

#ifndef OGClosure_h
#define OGClosure_h

#include <OpenGraph/OGBase.h>

OG_ASSUME_NONNULL_BEGIN

OG_EXTERN_C_BEGIN

typedef struct OGClosureStorage {
    const void *thunk;
    const void *_Nullable context;
} OGClosureStorage;

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGClosureStorage OGRetainClosure(void (*thunk)(void *_Nullable context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
                                 void *_Nullable context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGReleaseClosure(OGClosureStorage closure);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGClosure_h */
