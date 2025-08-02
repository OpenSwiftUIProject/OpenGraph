//
//  OGAttributeInfo.h
//  OpenGraphCxx

#ifndef OGAttributeInfo_h
#define OGAttributeInfo_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGAttributeType.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGAttributeInfo {
    const OGAttributeType* type;
    const void *body;
} OGAttributeInfo;

OG_ASSUME_NONNULL_END

#endif /* OGAttributeInfo_h */
