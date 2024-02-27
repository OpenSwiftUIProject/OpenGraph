//
//  OGWeakAttribute.h
//  
//
//  Created by Kyle on 2024/2/27.
//

#ifndef OGWeakAttribute_hpp
#define OGWeakAttribute_hpp

#include "OGBase.h"
#include "OGAttribute.h"

OG_ASSUME_NONNULL_BEGIN

typedef struct OGWeakAttribute {
    const OGAttribute raw_attribute;
    const uint32_t subgraph_id;
} OGWeakAttribute;

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGWeakAttribute OGCreateWeakAttribute(OGAttribute attribute) OG_SWIFT_NAME(OGWeakAttribute.init(attribute:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGWeakAttributeGetAttribute(OGWeakAttribute weakAttribute) OG_SWIFT_NAME(getter:OGWeakAttribute._attribute(self:));

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGWeakAttribute_h */
