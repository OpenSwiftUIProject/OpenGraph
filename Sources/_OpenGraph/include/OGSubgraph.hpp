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

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeID OGSubgraphGetTypeID();

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate(OGGraphRef cf_graph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate2(OGGraphRef cf_graph, OGAttribute attribute);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphGetCurrent();

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphSetCurrent(OGSubgraphRef cf_subgraph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphContextRef OGSubgraphGetCurrentGraphContext();

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphInvalidate(OGSubgraphRef cf_subgraph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphIsValid(OGSubgraphRef cf_subgraph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGSubgraphGetGraph(OGSubgraphRef cf_subgraph);

OG_EXTERN_C_END


#endif /* OGSubgraph_hpp */
