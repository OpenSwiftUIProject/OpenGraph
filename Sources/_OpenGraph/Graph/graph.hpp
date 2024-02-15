//
//  graph.hpp
//
//
//  Created by Kyle on 2024/1/18.
//

#ifndef graph_hpp
#define graph_hpp

#include "OGBase.hpp"
#if OG_OBJC_FOUNDATION
@class NSDictionary;
#endif /* OG_OBJC_FOUNDATION */

namespace OG {
class Graph {
    // TODO
    
    
public:
    #if OG_OBJC_FOUNDATION
    static CFTypeRef description(const Graph * graph, NSDictionary* dic);
    #endif /* OG_OBJC_FOUNDATION */
}; /* Graph */
} /* OG */

#endif /* graph_hpp */
