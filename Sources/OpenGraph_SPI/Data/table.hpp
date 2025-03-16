//
//  table.hpp
//  OpenGraph_SPI

#ifndef table_hpp
#define table_hpp

#include "OGBase.h"
#include "../Vector/vector.hpp"
#include <mach/vm_types.h>
#include <bitset>
#include <os/lock.h>

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
    static table &shared();
    
    table();
    
    OG_INLINE OG_CONSTEXPR
    vm_address_t data_base() const OG_NOEXCEPT { return _data_base; };

    OG_INLINE OG_CONSTEXPR
    vm_address_t region_base() const OG_NOEXCEPT { return _region_base; };

    OG_INLINE OG_CONSTEXPR
    void lock() const OG_NOEXCEPT { return os_unfair_lock_lock(&_lock); };

    OG_INLINE OG_CONSTEXPR
    void unlock() const OG_NOEXCEPT { return os_unfair_lock_unlock(&_lock); };

    OG_INLINE OG_CONSTEXPR
    uint32_t region_capacity() const OG_NOEXCEPT { return _region_capacity; };

    OG_INLINE OG_CONSTEXPR
    uint32_t data_capacity() const OG_NOEXCEPT { return _data_capacity; };

    OG_INLINE OG_CONSTEXPR
    uint32_t used_pages_num() const OG_NOEXCEPT { return _used_pages_num; };

    OG_INLINE OG_CONSTEXPR
    uint32_t reusable_pages_num() const OG_NOEXCEPT { return _reusable_pages_num; };

    void print() const OG_NOEXCEPT;

    void grow_region() OG_NOEXCEPT;

private:
    /// _region_base - page_size
    vm_address_t _data_base;

    vm_address_t _region_base;

    mutable os_unfair_lock _lock = OS_UNFAIR_LOCK_INIT;

    uint32_t _region_capacity;

    /// _region_capactiy + page_size
    uint32_t _data_capacity;

    uint32_t _used_pages_num = 0;

    uint32_t _reusable_pages_num = 0;

    uint32_t _map_search_start = 0;

    uint32_t _zones_num = 0;

    using remapped_region = std::pair<vm_address_t, int64_t>;
    vector<remapped_region, 0, uint32_t> _remapped_regions = {};
//
    constexpr static unsigned int pages_per_map = 64;
//    using page_map_type = std::bitset<pages_per_map>;
//    vector<page_map_type, 0, uint32_t> _page_maps = {};
//    vector<page_map_type, 0, uint32_t> _page_metadata_maps = {};

}; /* table */

} /* data */
} /* OG */

#endif /* table_hpp */
