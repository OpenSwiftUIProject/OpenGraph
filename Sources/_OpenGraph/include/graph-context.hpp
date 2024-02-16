//
//  graph-context.hpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef graph_context_hpp
#define graph_context_hpp

#include "OGBase.hpp"
#include "graph.hpp"

typedef struct OG_BRIDGED_TYPE(id) OG::Graph::Context * OGGraphContextRef;

class OG::Graph::Context final {
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
    

#endif /* graph_context_hpp */
