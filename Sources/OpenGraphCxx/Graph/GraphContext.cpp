//
//  GraphContext.cpp
//  OpenGraphCxx

#include <OpenGraphCxx/Graph/Graph.hpp>
#include <OpenGraph/OGGraph.h>
#include <OpenGraphCxx/Util/assert.hpp>

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
_invalidation_callback(nullptr),
_update_callback(nullptr) {
    // TODO
}

OG::Graph::Context::~Context() OG_NOEXCEPT {
    // TODO
}

const bool OG::Graph::Context::thread_is_updating() const OG_NOEXCEPT {
    return _graph->thread_is_updating() && _graph->is_context_updating(*this);
}
