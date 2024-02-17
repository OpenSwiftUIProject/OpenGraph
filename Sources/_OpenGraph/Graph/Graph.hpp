//
//  Graph.hpp
//
//
//  Created by Kyle on 2024/1/18.
//

#ifndef Graph_hpp
#define Graph_hpp

#include "OGBase.h"
#include "OGGraph.h"
#include "../Private/CFRuntime.h"

#if OG_OBJC_FOUNDATION
@class NSDictionary;
#endif /* OG_OBJC_FOUNDATION */

namespace OG {
class Graph final {
private:
    // TODO    
    static pthread_key_t _current_update_key;
public:
    #if OG_OBJC_FOUNDATION
    static CFTypeRef description(const Graph * graph, NSDictionary* dic);
    #endif /* OG_OBJC_FOUNDATION */
    
    // MARK: - pthread related
    
    OG_INLINE OG_CONSTEXPR
    const static pthread_key_t& current_key() OG_NOEXCEPT {
        return _current_update_key;
    }
    
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
}; /* Graph */
} /* OG */

struct OGGraphStorage {
    CFRuntimeBase base;
    OG::Graph::Context context;
};

struct OGGraphContextStorage {
    OG::Graph::Context context;
};

#endif /* Graph_hpp */