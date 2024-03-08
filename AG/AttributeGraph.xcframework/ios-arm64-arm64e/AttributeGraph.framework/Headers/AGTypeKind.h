//
//  AGTypeGetKind.h
//  
//
//  Created by Kyle on 2024/1/7.
//

#ifndef AGTypeKind_h
#define AGTypeKind_h

#include "AGBase.h"

typedef AG_ENUM(uint32_t, AGTypeKind) {
    AGTypeKindNone,
    AGTypeKindClass,
    AGTypeKindStruct,
    AGTypeKindEnum,
    AGTypeKindOptional,
    AGTypeKindTuple,
    AGTypeKindFunction,
    AGTypeKindExistential,
    AGTypeKindMetatype,
};

#endif /* AGTypeKind_h */
