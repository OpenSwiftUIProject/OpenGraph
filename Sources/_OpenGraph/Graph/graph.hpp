//
//  graph.hpp
//
//
//  Created by Kyle on 2024/1/18.
//

#ifndef graph_hpp
#define graph_hpp

#include "OGBase.hpp"
#if TARGET_OS_DARWIN && __OBJC__
@class NSDictionary;
#endif /* TARGET_OS_DARWIN */

namespace OG {
class Graph {
    // TODO
public:
    #if TARGET_OS_DARWIN && __OBJC__
    static CFDataRef description(const Graph * graph, NSDictionary* dic);
    #endif /* TARGET_OS_DARWIN */
}; /* Graph */
} /* OG */

#endif /* graph_hpp */
