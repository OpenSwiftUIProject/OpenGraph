//
//  OGSubgraph.cpp
//  OpenGraphCxx

#include <OpenGraph/OGSubgraph.h>
#include <OpenGraph/OGGraph.h>
#include <OpenGraphCxx/Graph/Subgraph.hpp>
#include <OpenGraph/OGGraphContext.h>
#include <OpenGraphCxx/Misc/assert.hpp>
#include <OpenGraphCxx/Misc/env.hpp>
#include <pthread.h>
#if !OG_TARGET_OS_WASI
#include <dispatch/dispatch.h>
#endif

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
    OG::Subgraph *subgraph = OG::Subgraph::get_current();
    if (subgraph == nullptr) {
        return nullptr;
    }
    return subgraph->to_cf();
}

void OGSubgraphSetCurrent(_Nullable OGSubgraphRef cf_subgraph) {
    OG::Subgraph *old_subgraph = OG::Subgraph::get_current();
    if (cf_subgraph == nullptr) {
        OG::Subgraph::set_current(nullptr);
    } else {
        OG::Subgraph *subgraph = cf_subgraph->subgraph;
        OG::Subgraph::set_current(subgraph);
        if (subgraph != nullptr) {
            CFRetain(cf_subgraph);
        }
    }
    if (old_subgraph != nullptr) {
        OGSubgraphRef old_cf_Subgraph = old_subgraph->to_cf();
        if (old_cf_Subgraph) {
            CFRelease(old_cf_Subgraph);
        }
    }
}

OGGraphContextRef OGSubgraphGetCurrentGraphContext() {
    OG::Subgraph *subgraph = OG::Subgraph::get_current();
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
    OGSubgraphAddChild2(parent, child, 0);
}

void OGSubgraphAddChild2(OGSubgraphRef parent, OGSubgraphRef child, uint8_t tag) {
    // TODO
}

void OGSubgraphRemoveChild(OGSubgraphRef parent, OGSubgraphRef child) {
    // TODO
}

OGSubgraphRef OGSubgraphGetChild(OGSubgraphRef cf_subgraph, uint32_t index, uint8_t *_Nullable tag_out) {
    // TODO
    return nullptr;
}

uint32_t OGSubgraphGetChildCount(OGSubgraphRef cf_subgraph) {
    // TODO
    return 0;
}

OGSubgraphRef OGSubgraphGetParent(OGSubgraphRef cf_subgraph, int64_t index) {
    // TODO
    return nullptr;
}

uint64_t OGSubgraphGetParentCount(OGSubgraphRef cf_subgraph) {
    // TODO
    return 0;
}

bool OGSubgraphIsAncestor(OGSubgraphRef cf_subgraph, OGSubgraphRef other) {
    // TODO
    return false;
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

void OGSubgraphUpdate(OGSubgraphRef cf_subgraph, OGAttributeFlags flags) {
    OG::Subgraph *subgraph = cf_subgraph->subgraph;
    if (subgraph == nullptr) {
        return;
    }
    // subgraph->update(flags);
}

bool OGSubgraphIsDirty(OGSubgraphRef cf_subgraph, OGAttributeFlags flags) {
    OG::Subgraph *subgraph = cf_subgraph->subgraph;
    if (subgraph == nullptr) {
        return false;
    }
    // TODO
    return false;
}

OGUniqueID OGSubgraphAddObserver(OGSubgraphRef cf_subgraph,
                                 const void (*function)(const void * _Nullable context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
                                 const void * _Nullable context) {
    OG::Subgraph *subgraph = cf_subgraph->subgraph;
    if (subgraph == nullptr) {
        OG::precondition_failure("accessing invalidated subgraph");
    }
    return subgraph->add_observer(OG::ClosureFunction<void>(function, context));
}

#if !OG_TARGET_OS_WASI
static bool should_record_tree;
static dispatch_once_t should_record_tree_once;

void init_should_record_tree(void * _Nullable context) {
    should_record_tree = OG::get_env("OG_TREE") != 0;
}
#endif

bool OGSubgraphShouldRecordTree() {
    #if !OG_TARGET_OS_WASI
    dispatch_once_f(&should_record_tree_once, NULL, init_should_record_tree);
    return should_record_tree;
    #else
    return false;
    #endif
}

void OGSubgraphSetShouldRecordTree() {
    #if !OG_TARGET_OS_WASI
    dispatch_once_f(&should_record_tree_once, NULL, init_should_record_tree);
    should_record_tree = true;
    #endif
}

void OGSubgraphBeginTreeElement(OGAttribute attribute, OGTypeID type, uint32_t flags) {
    OG::Subgraph * subgraph = OG::Subgraph::get_current();
    if (subgraph) {
        subgraph->begin_tree(attribute, reinterpret_cast<OG::swift::metadata const*>(type), flags);
    }
}

void OGSubgraphAddTreeValue(OGAttribute attribute, OGTypeID type, const char * key, uint32_t flags) {
    OG::Subgraph * subgraph = OG::Subgraph::get_current();
    if (subgraph) {
        subgraph->add_tree_value(attribute, reinterpret_cast<OG::swift::metadata const*>(type), key, flags);
    }
}

void OGSubgraphEndTreeElement(OGAttribute attribute) {
    OG::Subgraph * subgraph = OG::Subgraph::get_current();
    if (subgraph) {
        subgraph->end_tree(attribute);
    }
}
