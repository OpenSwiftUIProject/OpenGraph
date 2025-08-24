//
//  OGGraph.cpp
//  OpenGraphCxx

#include <OpenGraph/OGGraph.h>
#include <OpenGraphCxx/Graph/Graph.hpp>
#include <OpenGraphCxx/Misc/assert.hpp>
#include <OpenGraphCxx/Data/ClosureFunction.hpp>
#include <pthread.h>

OGGraphRef OGGraphCreate() {
    return OGGraphCreateShared(nullptr);
}

OGGraphRef OGGraphCreateShared(OGGraphRef storage) {
    const CFIndex extraSize = sizeof(OGGraphStorage)-sizeof(CFRuntimeBase);
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

void OGGraphResetProfile(_Nullable OGGraphRef graph) {
    // TODO
}

const void * _Nullable OGGraphGetContext(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return graph->context.get_context();
}

void OGGraphSetContext(OGGraphRef graph, const void * _Nullable context) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.set_context(context);
}

OGUnownedGraphContextRef OGGraphGetGraphContext(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return reinterpret_cast<OGUnownedGraphContextRef>(&graph->context.get_graph());
}

void OGGraphInvalidate(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        return;
    }
    graph->context.~Context();
    graph->context.setInvalid(true);
}

uint32_t OGGraphInternAttributeType(OGUnownedGraphContextRef graph, OGTypeID type,
                                    const OGAttributeType *(*make_attribute_type)(const void *context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
                                    const void *context) {
    // TODO
    return 0;
}

void OGGraphInvalidateAllValues(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.get_graph().value_mark_all();
}



void OGGraphSetInvalidationCallback(OGGraphRef graph,
                                    const void (*_Nullable function)(const void * _Nullable context OG_SWIFT_CONTEXT, OGAttribute) OG_SWIFT_CC(swift),
                                    const void * _Nullable context) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.set_invalidation_callback(OG::ClosureFunction<void, OGAttribute>(function, context));
}

void OGGraphSetUpdateCallback(OGGraphRef graph,
                               const void (*_Nullable function)(const void * _Nullable context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
                               const void * _Nullable context) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    graph->context.set_update_callback(OG::ClosureFunction<void>(function, context));
}

uint64_t OGGraphGetCounter(OGGraphRef graph, OGGraphCounterQueryType query) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    OG::Graph::Context& context = graph->context;
    switch (query) {
        case OGGraphCounterQueryTypeNodes:
            return context.get_graph().get_counter_0();
        case OGGraphCounterQueryTypeTransactions:
            return context.get_graph().get_counter_1();
        case OGGraphCounterQueryTypeUpdates:
            return context.get_graph().get_counter_2();
        case OGGraphCounterQueryTypeChanges:
            return context.get_graph().get_counter_3();
        case OGGraphCounterQueryTypeContextID:
            return context.get_graph().get_counter_4();
        case OGGraphCounterQueryTypeGraphID:
            return context.get_graph().get_counter_5();
        case OGGraphCounterQueryTypeContextThreadUpdating:
            return context.thread_is_updating();
        case OGGraphCounterQueryTypeThreadUpdating:
            return context.get_graph().thread_is_updating();
        case OGGraphCounterQueryTypeContextNeedsUpdate:
            return context.get_graph().get_counter_8();
        case OGGraphCounterQueryTypeNeedsUpdate:
            return context.get_graph().get_counter_9();
        case OGGraphCounterQueryTypeMainThreadUpdates:
            return context.get_graph().get_counter_10();
        default:
            return 0;
    }
}

void OGGraphSetUpdate(const void * _Nullable value) {
    pthread_setspecific(OG::Graph::current_key(), value);
}

const void * _Nullable OGGraphClearUpdate(void) {
    void * value = pthread_getspecific(OG::Graph::current_key());
    bool isDirty = (uint64_t)value & 0x1;
    if (value != nullptr && isDirty) {
        pthread_setspecific(OG::Graph::current_key(), (void *)((uint64_t)value | 0x1));
    }
    return value;
}

void OGGraphSetNeedsUpdate(OGGraphRef graph) {
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    // graph->context->set_needs_update();
}

bool OGGraphAnyInputsChanged(const OGAttribute *excluded_inputs, size_t count) {
    // TODO
    return false;
}
