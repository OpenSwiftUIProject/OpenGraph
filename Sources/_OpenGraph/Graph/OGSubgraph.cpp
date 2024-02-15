//
//  OGSubgraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "OGSubgraph.hpp"
#include "OGGraph.hpp"

OGSubgraphRef OGSubgraphCreate(OGGraphRef graph) {
    return OGSubgraphCreate2(graph/*, OGAttributeNil*/);
}

OGSubgraphRef OGSubgraphCreate2(OGGraphRef graph) {
    // TODO
    OG::Graph::Context::from_cf(graph);
}

namespace {
CFRuntimeClass &subgraph_type_id() {
    static auto dealloc = [](const void* ptr) {
        OGSubgraphRef storage = (OGSubgraphRef)ptr;
        auto subgraph = storage->subgraph;
        if (subgraph == nullptr) {
            return;
        }
//        subgraph->clear_object()
//        subgraph->invalidate_and_delete_(false)
    };
    static CFRuntimeClass klass = {
        0,
        "OGSubgraph",
        NULL,   // init
        NULL,   // copy
        dealloc,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return klass;
}
}

CFTypeID OGSubgraphGetTypeID() {
    static CFTypeID type = _CFRuntimeRegisterClass(&subgraph_type_id());
    return type;
}
