//
//  AGTypeID.h
//  
//
//  Created by Kyle on 2024/1/8.
//

#ifndef AGTypeID_h
#define AGTypeID_h

#include "AGBase.h"
#include "AGSwiftMetadata.h"
#include "AGTypeKind.h"

typedef const AGSwiftMetadata *AGTypeID AG_SWIFT_STRUCT;

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGTypeKind AGTypeGetKind(AGTypeID typeID) AG_SWIFT_NAME(getter:AGTypeID.kind(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * AGTypeNominalDescriptor(AGTypeID typeID) AG_SWIFT_NAME(getter:AGTypeID.nominalDescriptor(self:));

AG_EXTERN_C_END

#endif /* AGTypeID_h */
