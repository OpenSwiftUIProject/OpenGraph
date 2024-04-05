//
//  AGAttribute.h
//
//
//  Created by Kyle on 2023/8/30.
//

#ifndef AGAttribute_h
#define AGAttribute_h

#include "AGBase.h"
#include "AGAttributeInfo.h"
#include "AGAttributeFlags.h"
#include "AGCachedValueOptions.h"
#include "AGGraph.h"
#include "AGInputOptions.h"
#include "AGTypeID.h"
#include "AGValue.h"
#include "AGValueOptions.h"
#include "AGValueState.h"

AG_ASSUME_NONNULL_BEGIN

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
AGAttribute AGGraphCreateIndirectAttribute(AGAttribute attribute) AG_SWIFT_NAME(AGAttribute.createIndirect(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphCreateIndirectAttribute2(AGAttribute attribute, uint64_t size) AG_SWIFT_NAME(AGAttribute.createIndirect(self:size:));

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
const AGAttributeInfo AGGraphGetAttributeInfo(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.info(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphMutateAttribute(AGAttribute attribute,
                            const AGTypeID type,
                            bool invalidating,
                            const void (*function)(const void * _Nullable context AG_SWIFT_CONTEXT, void *body) AG_SWIFT_CC(swift),
                            const void * _Nullable context);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphGetIndirectDependency(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute._indirectDependency(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetIndirectDependency(AGAttribute attribute1, AGAttribute attribute2) AG_SWIFT_NAME(setter:AGAttribute._indirectDependency(self:_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphGetIndirectAttribute(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.source(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetIndirectAttribute(AGAttribute attribute1, AGAttribute attribute2) AG_SWIFT_NAME(setter:AGAttribute.source(self:_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGAttribute AGGraphCreateAttribute(long index, const void *body, const void * _Nullable value);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const AGValue AGGraphGetValue(AGAttribute attribute, AGValueOptions options, const AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGGraphSetValue(AGAttribute attribute, const void *value, const AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const AGValue AGGraphGetInputValue(AGAttribute attribute, AGAttribute inputAttribute, AGValueOptions options, const AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * _Nullable AGGraphGetOutputValue(AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetOutputValue(const void *value, const AGTypeID type);

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGValueState AGGraphGetValueState(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.valueState(self:));

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

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphVerifyType(AGAttribute attribute, AGTypeID type) AG_SWIFT_NAME(AGAttribute.verify(self:type:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphGetAttributeGraph(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.graph(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGSubgraphRef AGGraphGetAttributeSubgraph(AGAttribute attribute) AG_SWIFT_NAME(getter:AGAttribute.subgraph(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * AGGraphReadCachedAttribute(long hashValue, AGTypeID bodyType, const void *bodyPointer, AGTypeID valueType, AGCachedValueOptions options, AGAttribute attribute, bool unknown/*, ...*/);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * _Nullable AGGraphReadCachedAttributeIfExists(long hashValue, AGTypeID bodyType, const void *bodyPointer, AGTypeID valueType, AGCachedValueOptions options, AGAttribute attribute, bool unknown);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphWithUpdate(
    AGAttribute attribute,
    void (* callback)(const void *context AG_SWIFT_CONTEXT) AG_SWIFT_CC(swift),
    const void *context
);

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif /* AGAttribute_h */
