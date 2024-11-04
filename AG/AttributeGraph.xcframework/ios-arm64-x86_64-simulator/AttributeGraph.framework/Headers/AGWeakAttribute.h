//
//  AGWeakAttribute.h
//  
//
//  Created by Kyle on 2024/2/27.
//

#ifndef AGWeakAttribute_hpp
#define AGWeakAttribute_hpp

#include "AGBase.h"
#include "AGAttribute.h"

AG_ASSUME_NONNULL_BEGIN

typedef struct AGWeakAttribute {
    const AGAttribute raw_attribute;
    const uint32_t subgraph_id;
} AGWeakAttribute;

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGWeakAttribute AGCreateWeakAttribute(AGAttribute attribute);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGWeakAttributeGetAttribute(AGWeakAttribute weakAttribute);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGValue AGGraphGetWeakValue(AGWeakAttribute weakAttribute, AGValueOptions options, AGTypeID type);

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif /* AGWeakAttribute_h */
