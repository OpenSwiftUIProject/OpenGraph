//
//  OGAttributeInfo.h
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef OGAttributeInfo_h
#define OGAttributeInfo_h

#include <OpenGraphC/OGBase.h>
#include <OpenGraphC/OGAttributeType.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGAttributeInfo {
    const OGAttributeType* type;
    const void *body;
} OGAttributeInfo;

OG_ASSUME_NONNULL_END

#endif /* OGAttributeInfo_h */
