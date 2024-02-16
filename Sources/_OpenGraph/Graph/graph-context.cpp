//
//  graph-context.cpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#include "graph.hpp"
#include "OGGraph.hpp"
#include "../Util/assert.hpp"

OG::Graph::Context &OG::Graph::Context::from_cf(OGGraphRef storage) OG_NOEXCEPT {
    if (storage->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return storage->context;
}

OG::Graph::Context::Context(Graph &graph) OG_NOEXCEPT {
    // TODO
}



OG::Graph::Context::~Context() OG_NOEXCEPT {
    // TODO
}
