//
//  Graph.cpp
//  
//
//  Created by Kyle on 2024/1/18.
//

#include "Graph.hpp"
#include "Subgraph.hpp"

#if !OG_TARGET_OS_WASI
#include <dispatch/dispatch.h>
#endif
#include <pthread.h>

pthread_key_t OG::Graph::_current_update_key;

OG::Graph::Graph() OG_NOEXCEPT {
    // TODO
    
    // libdispatch is not supported on WASI
    // Tracked via https://github.com/swiftwasm/swift/issues/5565
    #if !OG_TARGET_OS_WASI
    static dispatch_once_t make_keys;
    dispatch_once_f(&make_keys, nullptr, [](void *context){
        pthread_key_create(&_current_update_key, nullptr);
        OG::Subgraph::make_current_subgraph_key();
    });
    #endif
    
    // TODO
}
