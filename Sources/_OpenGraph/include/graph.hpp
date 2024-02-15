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
private:
    
public:
    class Context final {
    private:
        Graph *_graph;
        bool _isInvalid;
    public:
        static Context &from_cf(OGGraphRef graph) OG_NOEXCEPT;
        Context(Graph &graph) OG_NOEXCEPT;
        ~Context() OG_NOEXCEPT;
        
        OG_INLINE OG_CONSTEXPR
        const bool has_graph() const OG_NOEXCEPT {
            return _graph != nullptr;
        }
        
        OG_INLINE OG_CONSTEXPR
        const Graph &get_graph() const OG_NOEXCEPT {
            return *_graph;
        }
        
        OG_INLINE OG_CONSTEXPR
        Graph &get_graph() OG_NOEXCEPT {
            return *_graph;
        }
        
        OG_INLINE OG_CONSTEXPR
        const bool isInvalid() const OG_NOEXCEPT {
            return _isInvalid;
        }
        
        OG_INLINE OG_CONSTEXPR
        void setInvalid(bool invalid) OG_NOEXCEPT {
            _isInvalid = invalid;
        }
    };
    #if OG_OBJC_FOUNDATION
    static CFTypeRef description(const Graph * graph, NSDictionary* dic);
    #endif /* OG_OBJC_FOUNDATION */
}; /* Graph */
} /* OG */


#endif /* graph_hpp */
