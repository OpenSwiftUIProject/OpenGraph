//
//  OGTypeID.h
//
//
//  Created by Kyle on 2024/1/8.
//

#ifndef OGTypeID_h
#define OGTypeID_h

#include "OGBase.h"
#include "OGSwiftMetadata.h"
#include "OGTypeKind.h"

typedef const OGSwiftMetadata *OGTypeID OG_SWIFT_STRUCT;

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OG_SWIFT_NAME(getter:OGTypeID.kind(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void * OGTypeNominalDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:OGTypeID.nominalDescriptor(self:));

OG_EXTERN_C_END

#endif /* OGTypeID_h */
