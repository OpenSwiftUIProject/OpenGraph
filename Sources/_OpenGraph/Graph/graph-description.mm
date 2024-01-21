//
//  graph-description.cpp
//
//
//  Created by Kyle on 2024/1/21.
//

#include "graph-description.hpp"

#if TARGET_OS_DARWIN
#include <Foundation/Foundation.h>

CFStringRef OGDescriptionFormat = CFSTR("format");

CFTypeRef OG::Graph::description(const Graph *graph, NSDictionary* dic) {
    // TODO
    // For "format": "graph/dict" - NSMutableDictionray
    // For "format": "graph/dot" - NSMutableString
    return NULL;
}
#endif /* TARGET_OS_DARWIN */
