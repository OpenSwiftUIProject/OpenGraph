//
//  OGSubgraph.hpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#ifndef OGSubgraph_hpp
#define OGSubgraph_hpp

#include "OGBase.hpp"
#include "subgraph.hpp"
#include "graph.hpp"
#include "../Private/CFRuntime.h"

struct OGSubgraphStorage {
    CFRuntimeBase base;
    OG::Subgraph *subgraph;
};

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate(OGGraphRef graph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate2(OGGraphRef graph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeID OGSubgraphGetTypeID();

OG_EXTERN_C_END


#endif /* OGSubgraph_hpp */
