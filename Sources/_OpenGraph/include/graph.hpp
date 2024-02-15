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

// https://github.com/apple/swift/blob/main/docs/CToSwiftNameTranslation.md#cf-types
typedef struct OG_BRIDGED_TYPE(id) OGGraphStorage * OGGraphRef;

namespace OG {
class Graph final {
    // TODO
    
public:
    class Context final {
    public:
        static Context &from_cf(OGGraphRef graph) OG_NOEXCEPT;
//        Context(Graph &graph) noexcept;
//        ~Context() noexcept;
    };
    #if OG_OBJC_FOUNDATION
    static CFTypeRef description(const Graph * graph, NSDictionary* dic);
    #endif /* OG_OBJC_FOUNDATION */
}; /* Graph */
} /* OG */


#endif /* graph_hpp */
