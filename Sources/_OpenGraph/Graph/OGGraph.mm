//
//  OGGraph.mm
//
//
//  Created by Kyle on 2024/2/15.
//

#include "OGGraph.hpp"
#include "../Util/assert.hpp"

OGGraphRef OGGraphCreate() {
    return OGGraphCreateShared(nullptr);
}

OGGraphRef OGGraphCreateShared(OGGraphRef storage) {
    const CFIndex extraSize = sizeof(OGGraphStorage)-sizeof(CFRuntimeBase);
    static_assert(extraSize == 0x10/*0x50*/);
    OGGraphRef instance = (OGGraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, OGGraphGetTypeID(), extraSize, nullptr);
    if (instance == nullptr) {
        OG::precondition_failure("memory allocation failure.");
    }
    OG::Graph *graph = nullptr;
    if (storage == nullptr) {
        graph = new OG::Graph();
    } else {
        if (storage->context.isInvalid()) {
            OG::precondition_failure("invalidated graph");
        }
        graph = &storage->context.get_graph();
        //  [graph+0x10c] += 1
    }
    // AG::Context(instance->graph, graph)
    
    //  [graph+0x10c] -= 1
//    if ([graph+0x10c] == 0) {
//        delete graph
//    }
    instance->context.setInvalid(false);
    return instance;
}

void OGGraphArchiveJSON(char const* name) {
    // TODO
}

CFTypeRef OGGraphDescription(OGGraphRef graph, CFDictionaryRef options) {
    #if OG_OBJC_FOUNDATION
    if (graph == nullptr) {
        return OG::Graph::description(nullptr, (__bridge NSDictionary*)options);
    }
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return OG::Graph::description(&graph->context.get_graph(), (__bridge NSDictionary*)options);
    #else
    return nullptr;
    #endif
}

namespace {
CFRuntimeClass &graph_type_id() {
    static auto dealloc = [](const void* ptr) {
        OGGraphRef storage = (OGGraphRef)ptr;
        if (storage->context.isInvalid()) {
            return;
        }
        storage->context.~Context();
    };
    static CFRuntimeClass klass = {
        0,
        "OGGraphStorage",
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

CFTypeID OGGraphGetTypeID() {
    static CFTypeID type = _CFRuntimeRegisterClass(&graph_type_id());
    return type;
}
