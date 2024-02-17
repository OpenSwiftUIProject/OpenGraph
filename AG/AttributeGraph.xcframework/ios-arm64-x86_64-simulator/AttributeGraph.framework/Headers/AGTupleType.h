//
//  AGTupleType.h
//  
//
//  Created by Kyle on 2024/1/25.
//

#ifndef AGTupleType_h
#define AGTupleType_h

#include "AGBase.h"
#include "AGSwiftMetadata.h"
#include "AGTypeID.h"

typedef const AGSwiftMetadata *AGTupleType AG_SWIFT_STRUCT;

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
long AGTupleCount(AGTupleType tupleType) AG_SWIFT_NAME(getter:AGTupleType.count(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
long AGTupleSize(AGTupleType tupleType) AG_SWIFT_NAME(getter:AGTupleType.size(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGTypeID AGTupleElementType(AGTupleType tupleType, long index);

AG_EXPORT
AG_REFINED_FOR_SWIFT
long AGTupleElementOffset(AGTupleType tupleType, long index) AG_SWIFT_NAME(AGTupleType.offset(self:at:));

AG_EXTERN_C_END
#endif /* AGTupleType_h */
