//
//  graph.cpp
//  
//
//  Created by Kyle on 2024/1/18.
//

#include "graph.hpp"
#include "../Util/assert.hpp"

#include <Foundation/Foundation.h>

OG::Graph* OGGraphCreate() {
    return OGGraphCreateShared(nullptr);
}

OG::Graph* OGGraphCreateShared(void *) {
    // TODO
    return nullptr;
}

void OGGraphArchiveJSON(char const* name) {
    // TODO
}

#if TARGET_OS_DARWIN && __OBJC__
CFTypeRef OGGraphDescription(OG::Graph* graph, NSDictionary* options) {
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
#endif /* TARGET_OS_DARWIN && __OBJC__ */
