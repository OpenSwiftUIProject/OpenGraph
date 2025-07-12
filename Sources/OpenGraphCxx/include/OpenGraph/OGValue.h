//
//  OGValue.h
//  OpenGraphCxx

#ifndef OGValue_h
#define OGValue_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGChangedValueFlags.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGValue {
    const void *value;
    OGChangedValueFlags flags;
} OGValue;

OG_ASSUME_NONNULL_END

#endif /* OGValue_h */
