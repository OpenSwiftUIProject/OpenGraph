//
//  OGTypeKind.hpp
//
//
//  Created by Kyle on 2024/1/7.
//

#ifndef OGTypeGetKind_hpp
#define OGTypeGetKind_hpp

#include "OGBase.hpp"
#include "OGTypeID.hpp"

typedef enum __attribute__((enum_extensibility(open))) OGTypeKind: uint32_t {
    OGTypeKindNone,
    OGTypeKindClass,
    OGTypeKindStruct,
    OGTypeKindEnum,
    OGTypeKindOptional,
    OGTypeKindTuple,
    OGTypeKindFunction,
    OGTypeKindExistential,
    OGTypeKindMetatype,
} OGTypeKind;

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OG_SWIFT_NAME(getter:OGTypeID.kind(self:));
OG_EXTERN_C_END

#endif /* OGTypeKind_hpp */
