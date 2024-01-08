//
//  OGTypeKind.hpp
//
//
//  Created by Kyle on 2024/1/7.
//

#ifndef OGTypeGetKind_hpp
#define OGTypeGetKind_hpp

#include <OpenFoundation/OpenFoundation.h>
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

OF_EXTERN_C_BEGIN
OF_EXPORT
OF_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OF_SWIFT_NAME(getter:OGTypeID.kind(self:));
OF_EXTERN_C_END

#endif /* OGTypeKind_hpp */
