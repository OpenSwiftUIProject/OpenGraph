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

typedef uint32_t OGAttribute __attribute((swift_newtype(struct)));

OG_EXTERN_C_BEGIN

OG_EXPORT
const OGAttribute OGAttributeNil;

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphGetCurrentAttribute(void) OG_SWIFT_NAME(getter:OGAttribute._current());

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateOffsetAttribute(OGAttribute attribute, uint64_t offset) OG_SWIFT_NAME(OGAttribute.create(self:offset:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateOffsetAttribute2(OGAttribute attribute, uint64_t offset, uint64_t size) OG_SWIFT_NAME(OGAttribute.create(self:offset:size:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttributeFlags OGGraphGetFlags(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.flags(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetFlags(OGAttribute attribute, OGAttributeFlags flags) OG_SWIFT_NAME(setter:OGAttribute.flags(self:_:));

OG_EXTERN_C_END

#endif /* OGAttribute_h */

