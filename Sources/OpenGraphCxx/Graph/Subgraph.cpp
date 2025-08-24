//
//  Subgraph.cpp
//  OpenGraphCxx

#include <OpenGraphCxx/Graph/Subgraph.hpp>
#include <OpenGraph/OGSubgraph.h>

pthread_key_t OG::Subgraph::_current_subgraph_key;

OG::Subgraph* OG::Subgraph::from_cf(OGSubgraphRef storage) OG_NOEXCEPT {
    return storage->subgraph;
}

void OG::Subgraph::clear_object() const OG_NOEXCEPT {
    // TODO
}

void OG::Subgraph::invalidate_and_delete_(bool) const OG_NOEXCEPT {
    // TODO
}

void OG::Subgraph::apply(OGAttributeFlags flags, OG::ClosureFunction<void, OGAttribute> body) const OG_NOEXCEPT {
    // TODO
}

OG::Subgraph::Subgraph(OG::SubgraphObject* object, OG::Graph::Context& context, OG::AttributeID):
_object(object), _graph(context.get_graph()), _graph_context_id(context.get_id()) {
    // TODO
}

OGUniqueID OG::Subgraph::add_observer(OG::ClosureFunction<void> observer) const OG_NOEXCEPT {
    // TODO
    return OGMakeUniqueID();
}

void OG::Subgraph::begin_tree(OG::AttributeID id, OG::swift::metadata const* type, unsigned int flags) const OG_NOEXCEPT {
    // TODO
}

void OG::Subgraph::add_tree_value(OG::AttributeID id, OG::swift::metadata const *type, const char* key, uint32_t flags) const OG_NOEXCEPT {
    // TODO
}

void OG::Subgraph::end_tree(OG::AttributeID id) const OG_NOEXCEPT {
    // TODO
}
