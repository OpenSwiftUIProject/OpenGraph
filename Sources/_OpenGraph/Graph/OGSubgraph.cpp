//
//  OGSubgraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "OGSubgraph.h"
#include "OGGraph.h"
#include "Subgraph.hpp"
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
    #if OG_TARGET_CPU_WASM32
    // FIXME: extraSize will always be 8 thus it will fail on WASM. Investate later.
    static_assert(extraSize == 8);
    #else
    static_assert(extraSize == sizeof(void *));
    #endif
    OGSubgraphRef cf_subgrah = (OGSubgraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, OGSubgraphGetTypeID(), extraSize, nullptr);
    if (cf_subgrah == nullptr) {
        OG::precondition_failure("memory allocation failure.");
    }
    cf_subgrah->subgraph = new OG::Subgraph((OG::SubgraphObject *)cf_subgrah, context, attribute);
    return cf_subgrah;
}

_Nullable OGSubgraphRef OGSubgraphGetCurrent() {
    OG::Subgraph* subgraph = (OG::Subgraph*)pthread_getspecific(OG::Subgraph::current_key());
    if (subgraph == nullptr) {
        return nullptr;
    }
    return subgraph->to_cf();
}

void OGSubgraphSetCurrent(_Nullable OGSubgraphRef cf_subgraph) {
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
        OGSubgraphRef cf_oldSubgraph = oldSubgraph->to_cf();
        if (cf_oldSubgraph) {
            CFRelease(cf_oldSubgraph);
        }
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

void OGSubgraphAddChild(OGSubgraphRef parent, OGSubgraphRef child) {
    // TODO
}

void OGSubgraphApply(OGSubgraphRef cf_subgraph,
                     OGAttributeFlags flags,
                     const void (*function)(const void * _Nullable context OG_SWIFT_CONTEXT, OGAttribute attribute) OG_SWIFT_CC(swift),
                     const void * _Nullable context) {
    if (cf_subgraph->subgraph == nullptr) {
        return;
    }
    return cf_subgraph->subgraph->apply(flags, OG::ClosureFunction<void, OGAttribute>(function, context));
}
