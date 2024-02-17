//
//  OGSubgraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "OGSubgraph.h"
#include "OGGraph.h"
#include "subgraph.hpp"
#include "../Util/assert.hpp"
#include <pthread.h>
#include "OGGraphContext.h"

namespace {
CFRuntimeClass &subgraph_type_id() {
    static auto dealloc = [](const void* ptr) {
        OGSubgraphRef storage = (OGSubgraphRef)ptr;
        auto subgraph = storage->subgraph;
        if (subgraph == nullptr) {
            return;
        }
        subgraph->clear_object();
        subgraph->invalidate_and_delete_(false);
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
        0,
    };
    return klass;
}
}

CFTypeID OGSubgraphGetTypeID() {
    static CFTypeID type = _CFRuntimeRegisterClass(&subgraph_type_id());
    return type;
}

OGSubgraphRef OGSubgraphCreate(OGGraphRef cf_graph) {
    return OGSubgraphCreate2(cf_graph, OGAttributeNil);
}

OGSubgraphRef OGSubgraphCreate2(OGGraphRef cf_graph, OGAttribute attribute) {
    OG::Graph::Context &context = OG::Graph::Context::from_cf(cf_graph);
    const CFIndex extraSize = sizeof(OGSubgraphStorage)-sizeof(CFRuntimeBase);
    static_assert(extraSize == 0x8);
    OGSubgraphRef cf_subgrah = (OGSubgraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, OGSubgraphGetTypeID(), extraSize, nullptr);
    if (cf_subgrah == nullptr) {
        OG::precondition_failure("memory allocation failure.");
    }
    cf_subgrah->subgraph = new OG::Subgraph((OG::SubgraphObject *)cf_subgrah, context, attribute);
    return cf_subgrah;
}

OGSubgraphRef OGSubgraphGetCurrent() {
    OG::Subgraph* subgraph = (OG::Subgraph*)pthread_getspecific(OG::Subgraph::current_key());
    if (subgraph == nullptr) {
        return nullptr;
    }
    return subgraph->to_cf();
}

void OGSubgraphSetCurrent(OGSubgraphRef cf_subgraph) {
    OG::Subgraph* oldSubgraph = (OG::Subgraph*)pthread_getspecific(OG::Subgraph::current_key());
    if (cf_subgraph == nullptr) {
        pthread_setspecific(OG::Subgraph::current_key(), nullptr);
    } else {
        pthread_setspecific(OG::Subgraph::current_key(), cf_subgraph->subgraph);
        if (cf_subgraph->subgraph != nullptr) {
            CFRetain(cf_subgraph);
        }
    }
    if (oldSubgraph != nullptr) {
        CFRelease(oldSubgraph->to_cf());
    }
}

OGGraphContextRef OGSubgraphGetCurrentGraphContext() {
    OG::Subgraph* subgraph = (OG::Subgraph*)pthread_getspecific(OG::Subgraph::current_key());
    if (subgraph == nullptr) {
        return nullptr;
    }
    return subgraph->get_context();
}

void OGSubgraphInvalidate(OGSubgraphRef cf_subgraph) {
    if (cf_subgraph->subgraph == nullptr) {
        return;
    }
    cf_subgraph->subgraph->invalidate_and_delete_(false);
}

bool OGSubgraphIsValid(OGSubgraphRef cf_subgraph) {
    if (cf_subgraph->subgraph == nullptr) {
        return false;
    }
    return !cf_subgraph->subgraph->isInvalid();
}

OGGraphRef OGSubgraphGetGraph(OGSubgraphRef cf_subgraph) {
    if (cf_subgraph->subgraph == nullptr) {
        OG::precondition_failure("accessing invalidated subgraph");
    }
    return OGGraphContextGetGraph(cf_subgraph->subgraph->get_context());
}
