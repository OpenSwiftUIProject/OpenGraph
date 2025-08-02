//
//  table.hpp
//  OpenGraphCxx

#ifndef table_hpp
#define table_hpp

#include <OpenGraphC/OGBase.h>
#include <OpenGraphCxx/Vector/vector.hpp>
#if OG_TARGET_OS_DARWIN
#include <mach/vm_types.h>
#else
typedef uintptr_t               vm_size_t;
typedef uintptr_t               vm_offset_t;
typedef vm_offset_t             vm_address_t;
#endif
#include <bitset>
#if OG_TARGET_OS_DARWIN
#include <os/lock.h>
#endif

namespace OG {
namespace data {
class zone;
class page;
template <typename T> class ptr;

class table {
public:
    class malloc_zone_deleter {
    };

public:
    static table &ensure_shared();

    OG_INLINE OG_CONSTEXPR
    vm_address_t data_base() const OG_NOEXCEPT { return _data_base; };

    OG_INLINE OG_CONSTEXPR
    vm_address_t region_base() const OG_NOEXCEPT { return _region_base; };

    OG_INLINE OG_CONSTEXPR
    void lock() const OG_NOEXCEPT {
        #if OG_TARGET_OS_DARWIN
        return os_unfair_lock_lock(&_lock);
        #endif
    };

    OG_INLINE OG_CONSTEXPR
    void unlock() const OG_NOEXCEPT {
        #if OG_TARGET_OS_DARWIN
        return os_unfair_lock_unlock(&_lock);
        #endif
    };

    OG_INLINE OG_CONSTEXPR
    uint32_t region_capacity() const OG_NOEXCEPT { return _region_capacity; };

    OG_INLINE OG_CONSTEXPR
    uint32_t data_capacity() const OG_NOEXCEPT { return _data_capacity; };

    OG_INLINE OG_CONSTEXPR
    uint32_t used_pages_num() const OG_NOEXCEPT { return _used_pages_num; };

    OG_INLINE OG_CONSTEXPR
    uint32_t reusable_pages_num() const OG_NOEXCEPT { return _reusable_pages_num; };

    OG_INLINE OG_CONSTEXPR
    uint32_t map_search_start() const OG_NOEXCEPT { return _map_search_start; };

    OG_INLINE OG_CONSTEXPR
    uint32_t zones_num() const OG_NOEXCEPT { return _zones_num; };

    OG_INLINE OG_CONSTEXPR
    uint32_t make_zone_id() {
        _zones_num += 1;
        return _zones_num;
    }

    table();

    void grow_region() OG_NOEXCEPT;

    void make_pages_reusable(uint32_t page_index, bool reusable) OG_NOEXCEPT;

    ptr<page> alloc_page(zone *zone, uint32_t size) OG_NOEXCEPT;

    void dealloc_page_locked(ptr<page> page) OG_NOEXCEPT;

    uint64_t raw_page_seed(ptr<page> page) OG_NOEXCEPT;

    void print() const OG_NOEXCEPT;
private:
    /// _region_base - page_size
    vm_address_t _data_base;

    vm_address_t _region_base;

    #if OG_TARGET_OS_DARWIN
    mutable os_unfair_lock _lock = OS_UNFAIR_LOCK_INIT;
    #endif

    uint32_t _region_capacity;

    /// _region_capactiy + page_size
    uint32_t _data_capacity;

    uint32_t _used_pages_num = 0;

    uint32_t _reusable_pages_num = 0;

    uint32_t _map_search_start = 0;

    uint32_t _zones_num = 0;

    using remapped_region = std::pair<vm_address_t, int64_t>;
    vector<remapped_region, 0, uint32_t> _remapped_regions = {};

    OG_CONSTEXPR static unsigned int pages_per_map = 64;

    using page_map_type = std::bitset<pages_per_map>;
    vector<page_map_type, 0, uint32_t> _page_maps = {};
    vector<page_map_type, 0, uint32_t> _page_metadata_maps = {};
}; /* table */

static uint8_t _shared_table_bytes[sizeof(table) / sizeof(uint8_t)] = {};

OG_INLINE
static table &shared_table() {
    return *reinterpret_cast<data::table *>(&_shared_table_bytes);
}

} /* data */
} /* OG */

#endif /* table_hpp */
