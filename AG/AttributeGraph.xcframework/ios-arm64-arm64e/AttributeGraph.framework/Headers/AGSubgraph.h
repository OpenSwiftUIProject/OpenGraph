//
//  AGSubgraph.h
//  
//
//  Created by Kyle on 2024/2/15.
//

#ifndef AGSubgraph_h
#define AGSubgraph_h

#include "AGBase.h"
#include "AGGraph.h"
#include "AGAttribute.h"
#include "CFRuntime.h"

AG_ASSUME_NONNULL_BEGIN

// MARK: - Exported C functions

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
CFTypeID AGSubgraphGetTypeID();

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGSubgraphRef AGSubgraphCreate(AGGraphRef cf_graph) AG_SWIFT_NAME(AGSubgraphRef.init(graph:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGSubgraphRef AGSubgraphCreate2(AGGraphRef cf_graph, AGAttribute attribute) AG_SWIFT_NAME(AGSubgraphRef.init(graph:attribute:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
_Nullable AGSubgraphRef AGSubgraphGetCurrent(void) AG_SWIFT_NAME(getter:AGSubgraphRef.current());

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGSubgraphSetCurrent(_Nullable AGSubgraphRef cf_subgraph) AG_SWIFT_NAME(setter:AGSubgraphRef.current(_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
_Nullable AGGraphContextRef AGSubgraphGetCurrentGraphContext(void) AG_SWIFT_NAME(getter:AGSubgraphRef.currentGraphContext());

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGSubgraphInvalidate(AGSubgraphRef cf_subgraph) AG_SWIFT_NAME(AGSubgraphRef.invalidate(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGSubgraphIsValid(AGSubgraphRef cf_subgraph) AG_SWIFT_NAME(getter:AGSubgraphRef.isValid(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGSubgraphGetGraph(AGSubgraphRef cf_subgraph) AG_SWIFT_NAME(getter:AGSubgraphRef.graph(self:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGSubgraphAddChild(AGSubgraphRef parent, AGSubgraphRef child) AG_SWIFT_NAME(AGSubgraphRef.addChild(self:_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGSubgraphApply(AGSubgraphRef cf_subgraph,
                     AGAttributeFlags flags,
                     const void (*function)(const void * _Nullable context AG_SWIFT_CONTEXT, AGAttribute attribute) AG_SWIFT_CC(swift),
                     const void * _Nullable context);

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END


#endif /* AGSubgraph_h */
