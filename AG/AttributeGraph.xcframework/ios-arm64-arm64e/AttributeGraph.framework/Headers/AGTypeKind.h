//
//  AGTypeGetKind.h
//  
//
//  Created by Kyle on 2024/1/7.
//

#ifndef AGTypeKind_h
#define AGTypeKind_h

#include "AGBase.h"
#include "AGTypeID.h"

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

AG_EXTERN_C_BEGIN
AG_EXPORT
AG_REFINED_FOR_SWIFT
AGTypeKind AGTypeGetKind(AGTypeID typeID) AG_SWIFT_NAME(getter:AGTypeID.kind(self:));
AG_EXTERN_C_END

#endif /* AGTypeKind_h */
