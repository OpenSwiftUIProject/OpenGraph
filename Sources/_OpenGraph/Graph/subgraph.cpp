//
//  subgraph.cpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#include "subgraph.hpp"
#include "OGSubgraph.hpp"

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

OG::Subgraph::Subgraph(OG::SubgraphObject*, OG::Graph::Context& context, OG::AttributeID):
_context(context){
}
