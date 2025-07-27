//
//  GraphDescription.mm
//
//
//  Created by Kyle on 2024/1/21.
//

#include "OGGraphDescription.h"
#include "OGGraph.h"
#include "Graph.hpp"
#include "../Util/assert.hpp"

#if OG_OBJC_FOUNDATION

#include <Foundation/Foundation.h>

const CFStringRef OGDescriptionFormat = CFSTR("format");
const CFStringRef OGDescriptionIncludeValues = CFSTR("include-values");

CFTypeRef OG::Graph::description(const Graph * _Nullable graph, NSDictionary* dic) {
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
