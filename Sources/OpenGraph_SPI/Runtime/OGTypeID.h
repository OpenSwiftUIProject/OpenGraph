//
//  OGTypeID.h
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#ifndef OGTypeID_h
#define OGTypeID_h

#include "OGBase.h"

OG_ASSUME_NONNULL_BEGIN

struct OGSwiftMetadata {};
typedef struct OGSwiftMetadata OGSwiftMetadata;

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
} OG_SWIFT_NAME(Metadata.Kind);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.kind(self:));

#if OPENGRAPH_RELEASE >= 2024

OG_EXPORT
OG_REFINED_FOR_SWIFT
void const* _Nullable OGTypeGetSignature(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.signature(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void const* _Nullable OGTypeGetDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.descriptor(self:));

#endif /* OPENGRAPH_RELEASE */

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFStringRef OGTypeDescription(OGTypeID typeID);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void const* _Nullable OGTypeNominalDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.nominalDescriptor(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
char const* _Nullable OGTypeNominalDescriptorName(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.nominalDescriptorName(self:));

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGTypeID_h */
