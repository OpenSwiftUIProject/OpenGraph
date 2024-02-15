//
//  OGSubgraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "OGSubgraph.hpp"
#include "OGGraph.hpp"
#include "../Util/assert.hpp"

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

OGSubgraphRef OGSubgraphCreate(OGGraphRef graph) {
    return OGSubgraphCreate2(graph, OGAttributeNil);
}

OGSubgraphRef OGSubgraphCreate2(OGGraphRef graph, OGAttribute attribute) {
    OG::Graph::Context &context = OG::Graph::Context::from_cf(graph);
    const CFIndex extraSize = sizeof(OGSubgraphStorage)-sizeof(CFRuntimeBase);
    static_assert(extraSize == 0x8);
    OGSubgraphRef instance = (OGSubgraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, OGSubgraphGetTypeID(), extraSize, nullptr);
    if (instance == nullptr) {
        OG::precondition_failure("memory allocation failure.");
    }
    instance->subgraph = new OG::Subgraph((OG::SubgraphObject *)instance, context, attribute);
}
