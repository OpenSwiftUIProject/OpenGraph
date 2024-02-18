//
//  OGAttribute.h
//  
//
//  Created by Kyle on 2023/9/25.
//

#ifndef OGAttribute_h
#define OGAttribute_h

#include "OGBase.h"
#include "OGAttributeFlags.h"
#include "OGInputOptions.h"
#include "OGAttributeInfo.h"
#include "OGTypeID.h"

OG_ASSUME_NONNULL_BEGIN

typedef uint32_t OGAttribute __attribute((swift_newtype(struct)));

OG_EXTERN_C_BEGIN

OG_EXPORT
const OGAttribute OGAttributeNil;

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphGetCurrentAttribute(void);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateOffsetAttribute(OGAttribute attribute, long offset) OG_SWIFT_NAME(OGAttribute.create(self:offset:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateOffsetAttribute2(OGAttribute attribute, long offset, uint64_t size) OG_SWIFT_NAME(OGAttribute.create(self:offset:size:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttributeFlags OGGraphGetFlags(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.flags(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetFlags(OGAttribute attribute, OGAttributeFlags flags) OG_SWIFT_NAME(setter:OGAttribute.flags(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphAddInput(OGAttribute attribute1, OGAttribute attribute2, OGInputOptions options, long token);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const OGAttributeInfo OGGraphGetAttributeInfo(OGAttribute attribute);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphMutateAttribute(OGAttribute attribute, const OGTypeID type, bool invalidating/*, closure*/);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphGetIndirectDependency(OGAttribute attribute);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetIndirectDependency(OGAttribute attribute1, OGAttribute attribute2);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateAttribute(long index, const void *body, const void * _Nullable value);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGAttribute_h */

