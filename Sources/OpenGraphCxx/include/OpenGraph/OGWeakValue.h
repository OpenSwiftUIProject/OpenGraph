//
//  OGWeakValue.h
//  OpenGraphCxx

#ifndef OGWeakValue_h
#define OGWeakValue_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGChangedValueFlags.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGWeakValue {
    const void * _Nullable value;
    OGChangedValueFlags flags;
} OGWeakValue;

OG_ASSUME_NONNULL_END

#endif /* OGWeakValue_h */
