//
//  AGTupleType.hpp
//  
//
//  Created by Kyle on 2024/1/25.
//

#ifndef AGTupleType_hpp
#define AGTupleType_hpp

#include "AGBase.hpp"
#include "AGSwiftMetadata.hpp"
#include "AGTypeID.hpp"

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

AG_EXTERN_C_END
#endif /* AGTupleType_hpp */
