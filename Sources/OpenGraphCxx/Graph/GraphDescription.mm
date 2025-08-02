//
//  GraphDescription.mm
//  OpenGraphCxx

#include <OpenGraphC/OGGraphDescription.h>
#include <OpenGraphC/OGGraph.h>
#include <OpenGraphCxx/Graph/Graph.hpp>
#include <OpenGraphCxx/Util/assert.hpp>

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

#endif /* OG_OBJC_FOUNDATION */
