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
AGSubgraphRef AGSubgraphCreate(_Nullable AGGraphRef cf_graph) AG_SWIFT_NAME(AGSubgraphRef.init(_:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGSubgraphRef AGSubgraphCreate2(_Nullable AGGraphRef cf_graph, AGAttribute attribute) AG_SWIFT_NAME(AGSubgraphRef.init(_:attribute:));

AG_EXPORT
AG_REFINED_FOR_SWIFT
_Nullable AGSubgraphRef AGSubgraphGetCurrent(void) AG_SWIFT_NAME(getter:AGSubgraphRef.current());

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGSubgraphSetCurrent(AGSubgraphRef cf_subgraph) AG_SWIFT_NAME(setter:AGSubgraphRef.current(_:));

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
AGGraphRef AGSubgraphGetGraph(AGSubgraphRef cf_subgraph);

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END


#endif /* AGSubgraph_h */
