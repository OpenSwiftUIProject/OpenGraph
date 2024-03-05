//
//  OGGraph.cpp
//
//
//  Created by Kyle on 2024/2/15.
//

#include "OGGraph.h"
#include "Graph.hpp"
#include "../Util/assert.hpp"

OGGraphRef OGGraphCreate() {
    return OGGraphCreateShared(nullptr);
}

OGGraphRef OGGraphCreateShared(OGGraphRef storage) {
    const CFIndex extraSize = sizeof(OGGraphStorage)-sizeof(CFRuntimeBase);
    #if OG_TARGET_CPU_WASM32
    // FIXME: extraSize will be 0x10 on WASM. Investate later.
    static_assert(extraSize == 0x10);
    #else
    static_assert(extraSize == 0x18/*0x50*/);
    #endif
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

void OGGraphArchiveJSON(char const * _Nullable name) {
    OG::Graph::write_to_file(nullptr, name);
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

void OGGraphStartProfiling(_Nullable OGGraphRef graph) {
    if (!graph) {
        OG::Graph::all_start_profiling(1);
        return;
    }
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.get_graph().start_profiling(1);
}

void OGGraphStopProfiling(_Nullable OGGraphRef graph) {
    if (!graph) {
        OG::Graph::all_stop_profiling();
        return;
    }
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.get_graph().stop_profiling();
}

void * _Nullable OGGraphGetContext(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return graph->context.get_context();
}

void OGGraphSetContext(OGGraphRef graph, void * _Nullable context) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.set_context(context);
}

OGGraphContextRef OGGraphGetGraphContext(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return reinterpret_cast<OGGraphContextRef>(reinterpret_cast<uintptr_t>(graph) + sizeof(CFRuntimeBase));
}

void OGGraphInvalidate(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        return;
    }
    graph->context.~Context();
    graph->context.setInvalid(true);
}

void OGGraphInvalidateAllValues(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.get_graph().value_mark_all();
}
