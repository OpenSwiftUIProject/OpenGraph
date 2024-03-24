//
//  AGGraph.h
//
//
//  Created by Kyle on 2024/2/5.
//

#ifndef AGGraph_h
#define AGGraph_h

#include "AGBase.h"
#include "CFRuntime.h"
#include "AGCounterQueryType.h"

// Note: Place all structure declaration in a single place to avoid header cycle dependency

typedef struct AG_BRIDGED_TYPE(id) AGGraphStorage * AGGraphRef;
typedef struct AG_BRIDGED_TYPE(id) AGGraphContextStorage * AGGraphContextRef;
typedef struct AG_BRIDGED_TYPE(id) AGSubgraphStorage * AGSubgraphRef;

struct AGGraphStorage;
struct AGGraphContextStorage;
struct AGSubgraphStorage;

typedef uint32_t AGAttribute __attribute((swift_newtype(struct)));

AG_ASSUME_NONNULL_BEGIN

// MARK: - Exported C functions

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreate(void) AG_SWIFT_NAME(AGGraphRef.init());

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreateShared(_Nullable AGGraphRef graph) AG_SWIFT_NAME(AGGraphRef.init(shared:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphArchiveJSON(char const * _Nullable name) AG_SWIFT_NAME(AGGraphRef.archiveJSON(name:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
_Nullable CFTypeRef AGGraphDescription(_Nullable AGGraphRef graph, CFDictionaryRef options) AG_SWIFT_NAME(AGGraphRef.description(_:options:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
CFTypeID AGGraphGetTypeID(void) AG_SWIFT_NAME(getter:AGGraphRef.typeID());

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphStartProfiling(_Nullable AGGraphRef graph);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphStopProfiling(_Nullable AGGraphRef graph);

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * _Nullable AGGraphGetContext(AGGraphRef graph) AG_SWIFT_NAME(getter:AGGraphRef.context(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetContext(AGGraphRef graph, const void * _Nullable context) AG_SWIFT_NAME(setter:AGGraphRef.context(self:_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphContextRef AGGraphGetGraphContext(AGGraphRef graph) AG_SWIFT_NAME(getter:AGGraphRef.graphContext(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphInvalidate(AGGraphRef graph) AG_SWIFT_NAME(AGGraphRef.invalidate(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphInvalidateAllValues(AGGraphRef graph) AG_SWIFT_NAME(AGGraphRef.invalidateAllValues(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetInvalidationCallback(AGGraphRef graph,
                                    const void (*_Nullable function)(const void * _Nullable context AG_SWIFT_CONTEXT, AGAttribute) AG_SWIFT_CC(swift),
                                    const void * _Nullable context);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetUpdateCallback(AGGraphRef graph,
                               const void (*_Nullable function)(const void * _Nullable context AG_SWIFT_CONTEXT) AG_SWIFT_CC(swift),
                               const void * _Nullable context);

AG_EXPORT
AG_REFINED_FOR_SWIFT
uint64_t AGGraphGetCounter(AGGraphRef graph, AGCounterQueryType query) AG_SWIFT_NAME(AGGraphRef.counter(self:for:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphSetUpdate(const void * _Nullable value) AG_SWIFT_NAME(AGGraphRef.setUpdate(_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
const void * _Nullable AGGraphClearUpdate(void) AG_SWIFT_NAME(AGGraphRef.clearUpdate());

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif /* AGGraph_h */
