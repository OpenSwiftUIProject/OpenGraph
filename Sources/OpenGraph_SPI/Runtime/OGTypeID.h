//
//  OGTypeID.h
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#ifndef OGTypeID_h
#define OGTypeID_h

#include "OGBase.h"
#include "OGSwiftMetadata.h"

OG_ASSUME_NONNULL_BEGIN

OG_EXTERN_C_BEGIN

typedef const OGSwiftMetadata *OGTypeID OG_SWIFT_STRUCT OG_SWIFT_NAME(Metadata);

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

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OG_SWIFT_NAME(getter:OGTypeID.kind(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFStringRef OGTypeDescription(OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void * OGTypeNominalDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:OGTypeID.nominalDescriptor(self:));

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGTypeID_h */
