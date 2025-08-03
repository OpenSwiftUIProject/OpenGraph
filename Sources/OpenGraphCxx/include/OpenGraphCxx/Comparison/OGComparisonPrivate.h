//
//  OGComparisonPrivate.h
//  OpenGraphCxx
//
//  Audited for 6.5.1
//  Status: Complete

#ifndef OGComparisonPrivate_h
#define OGComparisonPrivate_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGComparison.h>
#include <OpenGraph/OGTypeID.h>

OG_ASSUME_NONNULL_BEGIN

OG_EXTERN_C_BEGIN

typedef struct OGComparisonStateStorage {
    const void *destination;
    const void *source;
    OGFieldRange field_range;
    OGTypeID field_type;
} OGComparisonStateStorage;

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGComparisonPrivate_h */

