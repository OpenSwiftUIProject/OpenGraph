//
//  Subgraph.hpp
//  OpenGraphCxx

#ifndef Subgraph_hpp
#define Subgraph_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraphCxx/Graph/Graph.hpp>
#include <OpenGraphCxx/Attribute/AttributeID.hpp>
#include <OpenGraphCxx/Data/ClosureFunction.hpp>
#include <OpenGraphCxx/Runtime/metadata.hpp>
#include <pthread.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OG_BRIDGED_TYPE(id) OGSubgraphStorage * OGSubgraphRef;

namespace OG {
class SubgraphObject;

class Subgraph final {
private:
    SubgraphObject *_Nullable _object;
    Graph& _graph;
    OGUniqueID _graph_context_id;
    // TODO
    bool _isInvalid;
    static pthread_key_t _current_subgraph_key;
public:
    // MARK: - CF related
    
    static Subgraph *_Nullable from_cf(OGSubgraphRef cf_subgraph) OG_NOEXCEPT;
    
    _Nullable OGSubgraphRef to_cf() const OG_NOEXCEPT {
        return reinterpret_cast<OGSubgraphRef>(_object);
    }
    
    // MARK: - pthread related
    
    OG_INLINE
    const static void make_current_subgraph_key() OG_NOEXCEPT {
        pthread_key_create(&_current_subgraph_key, nullptr);
    }
    
    OG_INLINE OG_CONSTEXPR
    const static pthread_key_t& current_key() OG_NOEXCEPT {
        return _current_subgraph_key;
    }
    
    OG_INLINE OG_CONSTEXPR
    static Subgraph *_Nullable get_current() OG_NOEXCEPT {
        return (OG::Subgraph*)pthread_getspecific(OG::Subgraph::current_key());
    }
    
    OG_INLINE OG_CONSTEXPR
    static int set_current(Subgraph *_Nullable subgraph) OG_NOEXCEPT {
        return pthread_setspecific(OG::Subgraph::current_key(), subgraph);
    }
    
    // MARK: - Public API
    void clear_object() const OG_NOEXCEPT;
    void invalidate_and_delete_(bool) const OG_NOEXCEPT;
    
    void apply(OGAttributeFlags flags, OG::ClosureFunction<void, OGAttribute> body) const OG_NOEXCEPT;
    
    OGUniqueID add_observer(OG::ClosureFunction<void> observer) const OG_NOEXCEPT;
    
    void begin_tree(OG::AttributeID id, OG::swift::metadata const *type, uint32_t flags) const OG_NOEXCEPT;
    void add_tree_value(OG::AttributeID id, OG::swift::metadata const *type, const char* key, uint32_t flags) const OG_NOEXCEPT;
    void end_tree(OG::AttributeID id) const OG_NOEXCEPT;

    // MARK: - Init and deinit
    
    Subgraph(SubgraphObject*, OG::Graph::Context&, OG::AttributeID);
    
    // MARK: - Getter and setter
    
    OG_INLINE OG_CONSTEXPR
    const OG::Graph &get_graph() const OG_NOEXCEPT {
        return _graph;
    }

    OG_INLINE OG_CONSTEXPR
    OG::Graph &get_graph() OG_NOEXCEPT {
        return _graph;
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
    OG::Subgraph *_Nullable subgraph;
};

namespace OG {
class SubgraphObject final {
    OGSubgraphStorage storage;
};
}

#endif /* Subgraph_hpp */

OG_ASSUME_NONNULL_END
