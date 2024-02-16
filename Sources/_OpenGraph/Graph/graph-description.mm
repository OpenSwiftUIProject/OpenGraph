//
//  graph-description.cpp
//
//
//  Created by Kyle on 2024/1/21.
//

#include "graph-description.hpp"
#include "OGGraph.hpp"
#include "graph.hpp"
#include "../Util/assert.hpp"

#if OG_OBJC_FOUNDATION
#include <Foundation/Foundation.h>
CFStringRef OGDescriptionFormat = CFSTR("format");

CFTypeRef OG::Graph::description(const Graph *graph, NSDictionary* dic) {
    // TODO
    // For "format": "graph/dict" - NSMutableDictionray
    // For "format": "graph/dot" - NSMutableString
    return NULL;
}

CFTypeRef OGGraphDescription(OGGraphRef graph, CFDictionaryRef options) {
    if (graph == nullptr) {
        return OG::Graph::description(nullptr, (__bridge NSDictionary*)options);
    }
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return OG::Graph::description(&graph->context.get_graph(), (__bridge NSDictionary*)options);
}

#endif /* OG_OBJC_FOUNDATION */
