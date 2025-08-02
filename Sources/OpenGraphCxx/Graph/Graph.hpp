//
//  Graph.hpp
//  OpenGraphCxx


#ifndef Graph_hpp
#define Graph_hpp

#include "OGBase.h"
#include "OGGraph.h"
#include "OGUniqueID.h"
#include "../Private/CFRuntime.h"
#include "../Data/ClosureFunction.hpp"

OG_ASSUME_NONNULL_BEGIN

#if OG_OBJC_FOUNDATION
@class NSDictionary;
#endif /* OG_OBJC_FOUNDATION */

namespace OG {
class Graph final {
public:
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
        
        const bool thread_is_updating() const OG_NOEXCEPT;
        
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
private:
    static pthread_key_t _current_update_key;
    uint64_t _counter_4;
    uint32_t _counter_8;
    uint64_t _counter_0;
    bool _counter_9;
    uint64_t _counter_5;
    uint64_t _counter_1;
    uint64_t _counter_2;
    uint64_t _counter_10;
    uint64_t _counter_3;
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

    #if OG_OBJC_FOUNDATION
    static void write_to_file(const Graph * _Nullable, const char * _Nullable, uint8_t) OG_NOEXCEPT;
    #endif

    const bool thread_is_updating() const OG_NOEXCEPT;
    const bool is_context_updating(const OG::Graph::Context&) const OG_NOEXCEPT;
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_4() const OG_NOEXCEPT {
        return _counter_4;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint32_t get_counter_8() const OG_NOEXCEPT {
        return _counter_8;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_0() const OG_NOEXCEPT {
        return _counter_0;
    }
    
    OG_INLINE OG_CONSTEXPR
    const bool get_counter_9() const OG_NOEXCEPT {
        return _counter_9;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_5() const OG_NOEXCEPT {
        return _counter_5;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_1() const OG_NOEXCEPT {
        return _counter_1;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_2() const OG_NOEXCEPT {
        return _counter_2;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_10() const OG_NOEXCEPT {
        return _counter_10;
    }
    
    OG_INLINE OG_CONSTEXPR
    const uint64_t get_counter_3() const OG_NOEXCEPT {
        return _counter_3;
    }
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
