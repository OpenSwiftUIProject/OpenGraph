//
//  Subgraph.hpp
//
//
//  Created by Kyle on 2024/2/15.
//

#ifndef Subgraph_hpp
#define Subgraph_hpp

#include "OGBase.h"
#include "../Attribute/AttributeID.hpp"
#include "Graph.hpp"
#include <pthread.h>
#include "../Data/ClosureFunction.hpp"

typedef struct OG_BRIDGED_TYPE(id) OGSubgraphStorage * OGSubgraphRef;

namespace OG {
class SubgraphObject;

class Subgraph final {
private:
    OGSubgraphRef _cf_subgraph;
    OGGraphContextStorage& _context;
    // TODO
    bool _isInvalid;
    static pthread_key_t _current_subgraph_key;
public:
    // MARK: - CF related
    
    static Subgraph *from_cf(OGSubgraphRef cf_subgraph) OG_NOEXCEPT;
    
    OGSubgraphRef to_cf() const OG_NOEXCEPT {
        return _cf_subgraph;
    }
    
    // MARK: - pthread related
    
    static void make_current_subgraph_key() {
        pthread_key_create(&_current_subgraph_key, nullptr);
    }
    
    OG_INLINE OG_CONSTEXPR
    const static pthread_key_t& current_key() OG_NOEXCEPT {
        return _current_subgraph_key;
    }
    
    // MARK: - Public API
    void clear_object() const OG_NOEXCEPT;
    void invalidate_and_delete_(bool) const OG_NOEXCEPT;
    
    void apply(OGAttributeFlags flags, OG::ClosureFunction<void, OGAttribute> body) const OG_NOEXCEPT;
    
    // MARK: - Init and deinit
    
    Subgraph(SubgraphObject*, OG::Graph::Context&, OG::AttributeID);
    
    // MARK: - Getter and setter
    
    OG_INLINE OG_CONSTEXPR
    const OGGraphContextRef get_context() const OG_NOEXCEPT {
        return &_context;
    }
    
    OG_INLINE OG_CONSTEXPR
    OGGraphContextRef get_context() OG_NOEXCEPT {
        return &_context;
    }
    
    OG_INLINE OG_CONSTEXPR
    const bool isInvalid() const OG_NOEXCEPT {
        return _isInvalid;
    }
    
    OG_INLINE OG_CONSTEXPR
    void setInvalid(bool invalid) OG_NOEXCEPT {
        _isInvalid = invalid;
    }
}; /* Subgraph */
} /* OG */

struct OGSubgraphStorage {
    CFRuntimeBase base;
    OG::Subgraph *subgraph;
};

namespace OG {
class SubgraphObject final {
    OGSubgraphStorage storage;
};
}

#endif /* Subgraph_hpp */
