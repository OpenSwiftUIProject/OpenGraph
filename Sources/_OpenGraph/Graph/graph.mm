//
//  graph.cpp
//  
//
//  Created by Kyle on 2024/1/18.
//

#include "graph.hpp"
#include "OGGraph.hpp"
#include "../Util/assert.hpp"

OG::Graph::Context &OG::Graph::Context::from_cf(OGGraphRef storage) OG_NOEXCEPT {
    if (storage->invalid) {
        OG::precondition_failure("invalidated graph");
    }
    // TODO
//    return storage->graph;
}
