//
//  OGAttribute.h
//  
//
//  Created by Kyle on 2023/9/25.
//

#ifndef OGAttribute_h
#define OGAttribute_h

#include "OGBase.h"
#include "OGAttributeInfo.h"
#include "OGAttributeFlags.h"
#include "OGCachedValueOptions.h"
#include "OGGraph.h"
#include "OGInputOptions.h"
#include "OGTypeID.h"
#include "OGValue.h"
#include "OGValueOptions.h"
#include "OGValueState.h"

OG_ASSUME_NONNULL_BEGIN

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
OGAttribute OGGraphCreateIndirectAttribute(OGAttribute attribute) OG_SWIFT_NAME(OGAttribute.createIndirect(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateIndirectAttribute2(OGAttribute attribute, uint64_t size) OG_SWIFT_NAME(OGAttribute.createIndirect(self:size:));

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
const OGAttributeInfo OGGraphGetAttributeInfo(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.info(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphMutateAttribute(OGAttribute attribute,
                            const OGTypeID type,
                            bool invalidating,
                            const void (*function)(const void * _Nullable context OG_SWIFT_CONTEXT, void *body) OG_SWIFT_CC(swift),
                            const void * _Nullable context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphGetIndirectDependency(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute._indirectDependency(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetIndirectDependency(OGAttribute attribute1, OGAttribute attribute2) OG_SWIFT_NAME(setter:OGAttribute._indirectDependency(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphGetIndirectAttribute(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.source(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetIndirectAttribute(OGAttribute attribute1, OGAttribute attribute2) OG_SWIFT_NAME(setter:OGAttribute.source(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGGraphCreateAttribute(long index, const void *body, const void * _Nullable value);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const OGValue OGGraphGetValue(OGAttribute attribute, OGValueOptions options, const OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGGraphSetValue(OGAttribute attribute, const void *value, const OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const OGValue OGGraphGetInputValue(OGAttribute attribute, OGAttribute inputAttribute, OGValueOptions options, const OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void * _Nullable OGGraphGetOutputValue(OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetOutputValue(const void *value, const OGTypeID type);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGValueState OGGraphGetValueState(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.valueState(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGGraphHasValue(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.hasValue(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphUpdateValue(OGAttribute attribute) OG_SWIFT_NAME(OGAttribute.updateValue(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphPrefetchValue(OGAttribute attribute) OG_SWIFT_NAME(OGAttribute.prefetchValue(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphInvalidateValue(OGAttribute attribute) OG_SWIFT_NAME(OGAttribute.invalidateValue(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphVerifyType(OGAttribute attribute, OGTypeID type) OG_SWIFT_NAME(OGAttribute.verify(self:type:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphGetAttributeGraph(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.graph(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGGraphGetAttributeSubgraph(OGAttribute attribute) OG_SWIFT_NAME(getter:OGAttribute.subgraph(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void * OGGraphReadCachedAttribute(long hashValue, OGTypeID bodyType, const void *bodyPointer, OGTypeID valueType, OGCachedValueOptions options, OGAttribute attribute, bool unknown/*, ...*/);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void * _Nullable OGGraphReadCachedAttributeIfExists(long hashValue, OGTypeID bodyType, const void *bodyPointer, OGTypeID valueType, OGCachedValueOptions options, OGAttribute attribute, bool unknown);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphWithUpdate(
    OGAttribute attribute,
    void (* callback)(const void *context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
    const void *context
);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGAttribute_h */

