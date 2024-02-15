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
    // AGGraphGetTypeID(context)
    CFTypeID typeID;
    OGGraphRef instance = (OGGraphRef)_CFRuntimeCreateInstance(kCFAllocatorDefault, typeID, 0x50, nullptr);
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
        graph = storage->graph;
        //  [graph+0x10c] += 1
    }
    // AG::Context(instance->graph, graph)
    
    //  [graph+0x10c] -= 1
//    if ([graph+0x10c] == 0) {
//        delete graph
//    }
    instance->invalid = false;
    return nullptr;
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
