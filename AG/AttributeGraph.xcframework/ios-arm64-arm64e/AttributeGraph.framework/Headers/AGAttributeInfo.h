//
//  AGAttributeInfo.h
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef AGAttributeInfo_h
#define AGAttributeInfo_h

#include "AGBase.h"
#include "AGAttributeType.h"

AG_ASSUME_NONNULL_BEGIN

typedef struct AGAttributeInfo {
    const AGAttributeType* type;
    const void *body;
} AGAttributeInfo;

AG_ASSUME_NONNULL_END

#endif /* AGAttributeInfo_h */
