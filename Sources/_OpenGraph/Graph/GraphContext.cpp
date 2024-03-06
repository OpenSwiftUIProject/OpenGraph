//
//  GraphContext.cpp
//
//
//  Created by Kyle on 2024/2/16.
//

#include "Graph.hpp"
#include "OGGraph.h"
#include "../Util/assert.hpp"

OG::Graph::Context &OG::Graph::Context::from_cf(OGGraphRef storage) OG_NOEXCEPT {
    if (storage->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return storage->context;
}

OG::Graph::Context::Context(OG::Graph &graph) OG_NOEXCEPT :
_graph(&graph),
_context(nullptr),
_id(OGMakeUniqueID()),
_invalidation_function(nullptr),
_update_function(nullptr) {
    // TODO
}

OG::Graph::Context::~Context() OG_NOEXCEPT {
    // TODO
}
