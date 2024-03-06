//
//  Graph.hpp
//
//
//  Created by Kyle on 2024/1/18.
//

#ifndef Graph_hpp
#define Graph_hpp

#include "OGBase.h"
#include "OGGraph.h"
#include "../Private/CFRuntime.h"
#include "../Data/ClosureFunction.hpp"
#include "../Data/OGUniqueID.h"

OG_ASSUME_NONNULL_BEGIN

#if OG_OBJC_FOUNDATION
@class NSDictionary;
#endif /* OG_OBJC_FOUNDATION */

namespace OG {
class Graph final {
private:
    // TODO    
    static pthread_key_t _current_update_key;
public:
    #if OG_OBJC_FOUNDATION
    static CFTypeRef description(const Graph * _Nullable graph, NSDictionary* dic);
    #endif /* OG_OBJC_FOUNDATION */
    
    // MARK: - pthread related
    
    OG_INLINE OG_CONSTEXPR
    const static pthread_key_t& current_key() OG_NOEXCEPT {
        return _current_update_key;
    }
    
    Graph() OG_NOEXCEPT;
    
    const void value_mark_all() const OG_NOEXCEPT;
    
    static void all_start_profiling(uint32_t) OG_NOEXCEPT;
    static void all_stop_profiling() OG_NOEXCEPT;
    void start_profiling(uint32_t) OG_NOEXCEPT;
    void stop_profiling() OG_NOEXCEPT;
    
    static void write_to_file(const Graph * _Nullable, const char * _Nullable) OG_NOEXCEPT;
    
    class Context final {
    private:
        Graph * _Nullable _graph;
        const void * _Nullable _context;
        OGUniqueID _id;
        ClosureFunction<void, OGAttribute> _invalidation_callback;
        ClosureFunction<void> _update_callback;
        uint64_t unknown1;
        uint32_t unknown2;
        uint32_t unknown3;
        bool _isInvalid;
    public:
        static Context &from_cf(OGGraphRef graph) OG_NOEXCEPT;
        Context(Graph &graph) OG_NOEXCEPT;
        ~Context() OG_NOEXCEPT;
        
        OG_INLINE OG_CONSTEXPR
        const bool has_graph() const OG_NOEXCEPT {
            return _graph != nullptr;
        }
        
        OG_INLINE OG_CONSTEXPR
        const Graph &get_graph() const OG_NOEXCEPT {
            return *_graph;
        }
        
        OG_INLINE OG_CONSTEXPR
        Graph &get_graph() OG_NOEXCEPT {
            return *_graph;
        }
        
        OG_INLINE OG_CONSTEXPR
        const void * _Nullable get_context() const OG_NOEXCEPT {
            return _context;
        }
        
        OG_INLINE OG_CONSTEXPR
        void set_context(const void * _Nullable context) OG_NOEXCEPT {
            _context = context;
        }
        
        OG_INLINE
        void set_invalidation_callback(ClosureFunction<void, OGAttribute> invalidation_callback) OG_NOEXCEPT {
            _invalidation_callback = invalidation_callback;
        }
        
        OG_INLINE
        void set_update_callback(ClosureFunction<void> update_callback) OG_NOEXCEPT {
            _update_callback = update_callback;
        }
        
        OG_INLINE OG_CONSTEXPR
        const bool isInvalid() const OG_NOEXCEPT {
            return _isInvalid;
        }
        
        OG_INLINE OG_CONSTEXPR
        void setInvalid(bool invalid) OG_NOEXCEPT {
            _isInvalid = invalid;
        }
    };
    #if OG_TARGET_CPU_WASM32
    static_assert(sizeof(Context) == 0x38);
    #else
    static_assert(sizeof(Context) == 0x50);
    #endif
}; /* Graph */
} /* OG */

struct OGGraphStorage {
    CFRuntimeBase base;
    OG::Graph::Context context;
};

struct OGGraphContextStorage {
    OG::Graph::Context context;
};

OG_ASSUME_NONNULL_END

#endif /* Graph_hpp */
