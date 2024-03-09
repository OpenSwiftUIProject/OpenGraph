//
//  OGTypeKind.h
//
//
//  Created by Kyle on 2024/1/7.
//

#ifndef OGTypeGetKind_h
#define OGTypeGetKind_h

#include "OGBase.h"

typedef OG_ENUM(uint32_t, OGTypeKind) {
    OGTypeKindNone,
    OGTypeKindClass,
    OGTypeKindStruct,
    OGTypeKindEnum,
    OGTypeKindOptional,
    OGTypeKindTuple,
    OGTypeKindFunction,
    OGTypeKindExistential,
    OGTypeKindMetatype,
};

#endif /* OGTypeKind_h */
