//
//  OGTupleType.h
//  
//
//  Created by Kyle on 2024/1/25.
//

#ifndef OGTupleType_h
#define OGTupleType_h

#include "OGBase.h"
#include "OGSwiftMetadata.h"
#include "OGTypeID.h"

typedef const OGSwiftMetadata *OGTupleType OG_SWIFT_STRUCT;

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
long OGTupleCount(OGTupleType tupleType) OG_SWIFT_NAME(getter:OGTupleType.count(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
long OGTupleSize(OGTupleType tupleType) OG_SWIFT_NAME(getter:OGTupleType.size(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeID OGTupleElementType(OGTupleType tupleType, long index);

OG_EXPORT
OG_REFINED_FOR_SWIFT
long OGTupleElementOffset(OGTupleType tupleType, long index) OG_SWIFT_NAME(OGTupleType.offset(self:at:));

OG_EXTERN_C_END
#endif /* OGTupleType_h */
