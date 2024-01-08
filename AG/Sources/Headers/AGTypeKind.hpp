//
//  AGTypeGetKind.hpp
//  
//
//  Created by Kyle on 2024/1/7.
//

#ifndef AGTypeKind_hpp
#define AGTypeKind_hpp

#include <CoreFoundation/CoreFoundation.h>
#include "AGTypeID.hpp"

typedef enum __attribute__((enum_extensibility(open))) AGTypeKind: uint32_t {
    AGTypeKindNone,
    AGTypeKindClass,
    AGTypeKindStruct,
    AGTypeKindEnum,
    AGTypeKindOptional,
    AGTypeKindTuple,
    AGTypeKindFunction,
    AGTypeKindExistential,
    AGTypeKindMetatype,
} AGTypeKind;

CF_EXTERN_C_BEGIN
CF_EXPORT
CF_REFINED_FOR_SWIFT
AGTypeKind AGTypeGetKind(AGTypeID typeID) CF_SWIFT_NAME(getter:AGTypeID.kind(self:));
CF_EXTERN_C_END

#endif /* AGTypeKind_hpp */
