//
//  OGSubgraph.hpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#ifndef OGSubgraph_hpp
#define OGSubgraph_hpp

#include "OGBase.hpp"
#include "OGGraph.hpp"
#include "OGAttribute.hpp"
#include "../Private/CFRuntime.h"

OG_ASSUME_NONNULL_BEGIN

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeID OGSubgraphGetTypeID();

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate(_Nullable OGGraphRef cf_graph) OG_SWIFT_NAME(OGSubgraphRef.init(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate2(_Nullable OGGraphRef cf_graph, OGAttribute attribute) OG_SWIFT_NAME(OGSubgraphRef.init(_:attribute:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
_Nullable OGSubgraphRef OGSubgraphGetCurrent(void) OG_SWIFT_NAME(getter:OGSubgraphRef.current());

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphSetCurrent(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(setter:OGSubgraphRef.current(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphContextRef OGSubgraphGetCurrentGraphContext();

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphInvalidate(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(OGSubgraphRef.invalidate(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphIsValid(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(getter:OGSubgraphRef.isValid(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGSubgraphGetGraph(OGSubgraphRef cf_subgraph);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGSubgraph_hpp */
