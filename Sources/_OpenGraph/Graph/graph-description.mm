//
//  graph-description.cpp
//
//
//  Created by Kyle on 2024/1/21.
//

#include "graph-description.hpp"
#include "OGGraph.hpp"
#include "graph.hpp"

#if OG_OBJC_FOUNDATION
#include <Foundation/Foundation.h>
CFStringRef OGDescriptionFormat = CFSTR("format");

CFTypeRef OG::Graph::description(const Graph *graph, NSDictionary* dic) {
    // TODO
    // For "format": "graph/dict" - NSMutableDictionray
    // For "format": "graph/dot" - NSMutableString
    return NULL;
}
#endif /* OG_OBJC_FOUNDATION */
