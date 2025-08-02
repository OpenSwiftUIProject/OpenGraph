//
//  OGAttributeType.h
//  OpenGraphCxx

#ifndef OGAttributeType_h
#define OGAttributeType_h

#include "OGBase.h"
#include "OGTypeID.h"

OG_ASSUME_NONNULL_BEGIN

typedef struct OGAttributeType {
    OGTypeID typeID;
    OGTypeID valueTypeID;
    // TODO
} OGAttributeType;

OG_ASSUME_NONNULL_END

#endif /* OGAttributeType_h */
