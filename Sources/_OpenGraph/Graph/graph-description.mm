//
//  graph-description.cpp
//
//
//  Created by Kyle on 2024/1/21.
//

#include "graph-description.hpp"
#include <Foundation/Foundation.h>

#if TARGET_OS_DARWIN
CFStringRef OGDescriptionFormat = CFSTR("format");

void OGGraphArchiveJSON(char const* name) {
    // TODO
}

CFDataRef OG::Graph::description(const Graph *graph, NSDictionary* dic) {
    // TODO
    return NULL;
}
#endif /* TARGET_OS_DARWIN */
