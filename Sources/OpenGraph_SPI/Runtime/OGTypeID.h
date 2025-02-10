//
//  OGTypeID.h
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: Complete

#ifndef OGTypeID_h
#define OGTypeID_h

#include "OGBase.h"
#include "OGVersion.h"

OG_ASSUME_NONNULL_BEGIN

typedef struct OG_SWIFT_NAME(_Metadata) OGSwiftMetadata {
} OGSwiftMetadata;

typedef const OGSwiftMetadata *OGTypeID OG_SWIFT_STRUCT OG_SWIFT_NAME(Metadata);

typedef OG_CLOSED_ENUM(uint32_t, OGTypeKind) {
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

typedef OG_OPTIONS(uint32_t, OGTypeApplyOptions) {
    OGTypeApplyOptions_0 = 0,
    OGTypeApplyOptions_1 = 1 << 0,
    OGTypeApplyOptions_2 = 1 << 1,
    OGTypeApplyOptions_4 = 1 << 2,
};

#if OPENGRAPH_RELEASE >= OPENGRAPH_RELEASE_2024

typedef struct OG_SWIFT_NAME(Signature) OGTypeSignature {
    uint32_t bytes[5];
} OGTypeSignature;

#endif

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeKind OGTypeGetKind(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.kind(self:));

// TODO
// OGOverrideComparisonForTypeDescriptor();

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTypeApplyFields(const void *type, const void *block, void *context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGTypeApplyFields2(const void *type, OGTypeApplyOptions options, const void *block, void *context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
uint32_t OGTypeGetEnumTag(OGTypeID typeID, const void *value) OG_SWIFT_NAME(Metadata.enumTag(self:_:));

#if OPENGRAPH_RELEASE >= OPENGRAPH_RELEASE_2024

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTypeProjectEnumData(OGTypeID typeID, void *value) OG_SWIFT_NAME(Metadata.projectEnumData(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTypeInjectEnumTag(OGTypeID typeID, uint32_t tag, void *value) OG_SWIFT_NAME(Metadata.injectEnumTag(self:tag:_:));

#endif /* OPENGRAPH_RELEASE */

// TODO
OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGTypeApplyEnumData();

// TODO
OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGTypeApplyMutableEnumData();

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFStringRef OGTypeDescription(OGTypeID typeID);

#if OPENGRAPH_RELEASE >= OPENGRAPH_RELEASE_2024

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeSignature const OGTypeGetSignature(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.signature(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void const* _Nullable OGTypeGetDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.descriptor(self:));

#endif /* OPENGRAPH_RELEASE */

OG_EXPORT
OG_REFINED_FOR_SWIFT
void const* _Nullable OGTypeNominalDescriptor(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.nominalDescriptor(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
char const* _Nullable OGTypeNominalDescriptorName(OGTypeID typeID) OG_SWIFT_NAME(getter:Metadata.nominalDescriptorName(self:));

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGTypeID_h */
