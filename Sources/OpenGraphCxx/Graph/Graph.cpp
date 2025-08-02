//
//  Graph.cpp
//  OpenGraphCxx

#include <OpenGraphCxx/Graph/Graph.hpp>
#include <OpenGraphCxx/Graph/Subgraph.hpp>
#include <OpenGraph/OGGraphDescription.h>

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
    dispatch_once_f(&make_keys, nullptr, [](void * _Nullable context){
        pthread_key_create(&_current_update_key, nullptr);
        OG::Subgraph::make_current_subgraph_key();
    });
    #endif

    // TODO
}

const void OG::Graph::value_mark_all() const OG_NOEXCEPT {
    // TODO
}

void OG::Graph::all_start_profiling(uint32_t) OG_NOEXCEPT {
    // TODO
}
void OG::Graph::all_stop_profiling() OG_NOEXCEPT {
    // TODO
}
void OG::Graph::start_profiling(uint32_t) OG_NOEXCEPT {
    // TODO
}
void OG::Graph::stop_profiling() OG_NOEXCEPT {
    // TODO
}

const bool OG::Graph::thread_is_updating() const OG_NOEXCEPT {
    void *current = pthread_getspecific(current_key());
    if (!current) {
        return false;
    }
    // TODO
    return false;
}

const bool OG::Graph::is_context_updating(const OG::Graph::Context&) const OG_NOEXCEPT {
    // TODO
    return false;
}
