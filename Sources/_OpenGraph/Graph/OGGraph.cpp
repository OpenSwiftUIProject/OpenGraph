//
//  OGGraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "OGGraph.hpp"
#include "../Util/assert.hpp"

//#if TARGET_OS_DARWIN
//#include <Foundation/Foundation.h>
//#endif

OGGraphRef OGGraphCreate() {
    return OGGraphCreateShared(nullptr);
}

OGGraphRef OGGraphCreateShared(OGGraphRef storage) {
    const CFIndex extraSize = sizeof(OGGraphStorage)-sizeof(CFRuntimeBase);
    static_assert(extraSize == 0x8/*0x50*/, "");
    OGGraphRef instance = (OGGraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, OGGraphGetTypeID(), extraSize, nullptr);
    if (instance == nullptr) {
        OG::precondition_failure("memory allocation failure.");
    }
    OG::Graph *graph = nullptr;
    if (storage == nullptr) {
        graph = new OG::Graph();
    } else {
        if (storage->invalid) {
            OG::precondition_failure("invalidated graph");
        }
//        graph = storage->context;
        //  [graph+0x10c] += 1
    }
    // AG::Context(instance->graph, graph)
    
    //  [graph+0x10c] -= 1
//    if ([graph+0x10c] == 0) {
//        delete graph
//    }
    instance->invalid = false;
    return instance;
}

void OGGraphArchiveJSON(char const* name) {
    // TODO
}

#if OG_OBJC_FOUNDATION
CFTypeRef OGGraphDescription(OG::Graph* graph, CFDictionary* options) {
    if (graph) {
        // TODO
        if (false/* graph+0x58 */) {
            OG::precondition_failure("invalidated graph");
        }
        return OG::Graph::description(graph/* graph+0x10 */, options);
    } else {
        return OG::Graph::description(graph, options);
    }
}
#endif /* OG_OBJC_FOUNDATION */

namespace {
CFRuntimeClass &graph_type_id() {
    static auto dealloc = [](const void* ptr) {
        OGGraphRef storage = (OGGraphRef)ptr;
        if (storage->invalid) {
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
        NULL,
    };
    return klass;
}
}

CFTypeID OGGraphGetTypeID() {
    static CFTypeID type = _CFRuntimeRegisterClass(&graph_type_id());
    return type;
}
