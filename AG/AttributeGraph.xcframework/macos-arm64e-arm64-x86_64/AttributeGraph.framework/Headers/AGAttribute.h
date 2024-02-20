//
//  AGAttribute.h
//
//
//  Created by Kyle on 2023/8/30.
//


#ifndef AGAttribute_h
#define AGAttribute_h

#include "AGBase.h"
#include "AGAttributeFlags.h"
#include "AGInputOptions.h"
#include "AGAttributeInfo.h"
#include "AGTypeID.h"
#include "AGValue.h"
#include "AGValueOptions.h"

AG_ASSUME_NONNULL_BEGIN

typedef uint32_t AGAttribute __attribute((swift_newtype(struct)));

AG_EXTERN_C_BEGIN

AG_EXPORT
const AGAttribute AGAttributeNil;

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphGetCurrentAttribute(void);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphCreateOffsetAttribute(AGAttribute attribute, long offset) AG_SWIFT_NAME(AGAttribute.create(self:offset:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphCreateOffsetAttribute2(AGAttribute attribute, long offset, uint64_t size) AG_SWIFT_NAME(AGAttribute.create(self:offset:size:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttributeFlags AGGraphGetFlags(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.flags(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetFlags(AGAttribute attribute, AGAttributeFlags flags) AG_SWIFT_NAME(setter:AGAttribute.flags(self:_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphAddInput(AGAttribute attribute1, AGAttribute attribute2, AGInputOptions options, long token);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const AGAttributeInfo AGGraphGetAttributeInfo(AGAttribute attribute);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphMutateAttribute(AGAttribute attribute, const AGTypeID type, bool invalidating/*, closure*/);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphGetIndirectDependency(AGAttribute attribute);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetIndirectDependency(AGAttribute attribute1, AGAttribute attribute2);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphCreateAttribute(long index, const void *body, const void * _Nullable value);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGValue AGGraphGetValue(AGAttribute attribute, AGValueOptions options, AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGGraphSetValue(AGAttribute attribute, const void *value, AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGGraphHasValue(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.hasValue(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphUpdateValue(AGAttribute attribute) AG_SWIFT_NAME(AGAttribute.updateValue(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphPrefetchValue(AGAttribute attribute) AG_SWIFT_NAME(AGAttribute.prefetchValue(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphInvalidateValue(AGAttribute attribute) AG_SWIFT_NAME(AGAttribute.invalidateValue(self:));

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif /* AGAttribute_h */
