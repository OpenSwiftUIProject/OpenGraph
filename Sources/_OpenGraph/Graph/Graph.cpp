//
//  Graph.cpp
//  
//
//  Created by Kyle on 2024/1/18.
//

#include "Graph.hpp"
#include <dispatch/dispatch.h>
#include <pthread.h>
#include "Subgraph.hpp"

pthread_key_t OG::Graph::_current_update_key;

OG::Graph::Graph() OG_NOEXCEPT {
    // TODO
    static dispatch_once_t make_keys;
    dispatch_once_f(&make_keys, nullptr, [](void *context){
        pthread_key_create(&_current_update_key, nullptr);
        OG::Subgraph::make_current_subgraph_key();
    });
    // TODO
}
