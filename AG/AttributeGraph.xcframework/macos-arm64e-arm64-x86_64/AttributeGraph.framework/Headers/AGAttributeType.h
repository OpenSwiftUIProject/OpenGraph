//
//  AGAttributeType.h
//  
//
//  Created by Kyle on 2024/2/17.
//

#ifndef AGAttributeType_h
#define AGAttributeType_h

#include "AGBase.h"
#include "AGTypeID.h"

AG_ASSUME_NONNULL_BEGIN

typedef struct AGAttributeType {
    AGTypeID typeID;
    AGTypeID valueTypeID;
    // TODO
} AGAttributeType;

AG_ASSUME_NONNULL_END

#endif /* AGAttributeType_h */
