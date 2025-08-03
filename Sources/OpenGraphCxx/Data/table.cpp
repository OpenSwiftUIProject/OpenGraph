//
//  table.cpp
//  OpenGraphCxx
//
//  Audited for 6.5.1
//  Status: WIP
//  Modified based Compute code

#include <OpenGraphCxx/Data/table.hpp>
#include <OpenGraphCxx/Data/page.hpp>
#include <OpenGraphCxx/Data/page_const.hpp>
#include <OpenGraphCxx/Data/zone.hpp>
#include <OpenGraphCxx/Util/assert.hpp>
#include <sys/mman.h>
#include <dispatch/dispatch.h>
#if OG_TARGET_OS_DARWIN
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#if OG_TARGET_OS_DARWIN
#include <mach/mach.h>
#endif

void *OGGraphVMRegionBaseAddress;

namespace OG {
namespace data {

#if OG_TARGET_OS_DARWIN
malloc_zone_t *table::_malloc_zone = nullptr;
#endif

table &table::ensure_shared() {
    static dispatch_once_t once;
    dispatch_once_f(&once, nullptr, [](void *_Nullable context){
         new (_shared_table_bytes) table();
    });
    return shared_table();
}

table::table() {
    constexpr vm_size_t initial_size = 32 * pages_per_map * page_size;
    _region_capacity = initial_size;
    void *region = mmap(nullptr, initial_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    _region_base = reinterpret_cast<vm_address_t>(region);
    OGGraphVMRegionBaseAddress = region;
    if (region == MAP_FAILED) {
        OG::precondition_failure("memory allocation failure (%u bytes, %u)", _region_capacity, errno);
    }
    _data_base = reinterpret_cast<vm_address_t>(region) - page_size;
    _data_capacity = initial_size + page_size;
    #if OG_TARGET_OS_DARWIN
    if (_malloc_zone == nullptr) {
        malloc_zone_t *zone = malloc_create_zone(0, 0);
        _malloc_zone = zone;
        malloc_set_zone_name(zone, "OpenGraph graph data");
    }
    #else
    precondition_failure("not implemented");
    #endif
}

void table::grow_region() OG_NOEXCEPT {
    #if OG_TARGET_OS_DARWIN
    uint32_t new_size = 4 * _region_capacity;
    // Check size does not exceed 32 bits
    if (new_size <= _region_capacity) {
        precondition_failure("exhausted data space");
    }
    void *new_region = mmap(nullptr, new_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (new_region == MAP_FAILED) {
        precondition_failure("memory allocation failure (%u bytes, %u)", new_size, errno);
    }

    vm_prot_t cur_protection = VM_PROT_NONE;
    vm_prot_t max_protection = VM_PROT_NONE;
    kern_return_t error = vm_remap(mach_task_self(),
                                   reinterpret_cast<vm_address_t *>(&new_region),
                                   _region_capacity,
                                   0,
                                   VM_FLAGS_OVERWRITE,
                                   mach_task_self(),
                                   reinterpret_cast<vm_address_t>(_region_base),
                                   false,
                                   &cur_protection,
                                   &max_protection,
                                   VM_INHERIT_NONE);
    if (error) {
        precondition_failure("vm_remap failure: 0x%x", error);
    }
    _remapped_regions.push_back({this->region_base(), this->region_capacity()});
    OGGraphVMRegionBaseAddress = new_region;
    _data_base = reinterpret_cast<vm_address_t>(new_region) - page_size;
    _region_base = reinterpret_cast<vm_address_t>(new_region);
    _region_capacity = new_size;
    _data_capacity = new_size + page_size;
    #else
    precondition_failure("not implemented");
    #endif
}

void table::make_pages_reusable(uint32_t page_index, bool reusable) OG_NOEXCEPT {
    #if OG_TARGET_OS_DARWIN
    static constexpr uint32_t mapped_pages_size = page_size * pages_per_map; // 64 * 512 = 0x8000
    void *mapped_pages_address = reinterpret_cast<void *>(region_base() + ((page_index * page_size) & ~(mapped_pages_size - 1)));
    int advice = reusable ? MADV_FREE_REUSABLE : MADV_FREE_REUSE;
    madvise(mapped_pages_address, mapped_pages_size, advice);
    static bool unmap_reusable = []() -> bool {
        char *result = getenv("OG_UNMAP_REUSABLE");
        if (result) {
            return atoi(result) != 0;
        }
        return false;
    }();
    if (unmap_reusable) {
        int protection = reusable ? PROT_NONE : (PROT_READ | PROT_WRITE);
        mprotect(mapped_pages_address, mapped_pages_size, protection);
    }
    _reusable_pages_num += reusable ? mapped_pages_size : -mapped_pages_size;
    #else
    precondition_failure("not implemented");
    #endif
}

// TO BE AUDITED
ptr<page> table::alloc_page(zone *zone, uint32_t needed_size) OG_NOEXCEPT {
    lock();

    uint32_t needed_pages = (needed_size + page_mask) / page_size;

    // assume we'll have to append a new page
    uint32_t new_page_index = _page_maps.size() * pages_per_map;

    // scan for consecutive free pages
    if (!_page_maps.empty() && _used_pages_num <= _page_maps.size() * pages_per_map) {

        uint32_t start_map_index = _map_search_start;
        for (int i = 0; i < _page_maps.size(); i++) {
            int map_index = start_map_index + i;
            if (map_index >= _page_maps.size()) {
                map_index -= _page_maps.size(); // wrap around
            }

            page_map_type free_pages_map = _page_maps[map_index].flip();
            while (free_pages_map.any()) {

                int candidate_bit = std::countr_zero(static_cast<uint64_t>(free_pages_map.to_ullong()));

                // scan ahead to find enough consecutive free pages
                bool found = false;
                if (needed_pages > 1) {
                    for (int j = 1; j < needed_pages; j++) {
                        int next_page_index = (map_index * pages_per_map) + candidate_bit + j;
                        int next_map_index = next_page_index / pages_per_map;
                        if (next_map_index == _page_maps.size()) {
                            // There are not enough maps, but the trailing pages are contiguous so this page is
                            // usable
                            found = true;
                            break;
                        }
                        if (_page_maps[next_map_index].test(next_page_index % pages_per_map)) {
                            // next page is used, remove this page from free_pages_map
                            free_pages_map.reset(candidate_bit);
                            break;
                        }
                    }
                    found = true;
                } else {
                    // only need one page
                    found = true;
                }

                if (found) {
                    new_page_index = (map_index * pages_per_map) + candidate_bit;
                    _map_search_start = map_index;
                    break;
                }
            }
        }
    }

    // update maps
    for (int i = 0; i < needed_pages; i++) {
        uint32_t page_index = new_page_index + i;
        uint32_t map_index = page_index / pages_per_map;

        if (map_index == _page_maps.size()) {
            _page_maps.push_back(0);
            _page_metadata_maps.push_back(0);
        } else if (_page_maps[map_index] == 0) {
            make_pages_reusable(page_index, false);
        }

        _page_maps[map_index].set(page_index % pages_per_map);
        if (i == 0) {
            _page_metadata_maps[map_index].set(page_index % pages_per_map);
        }
    }

    _used_pages_num += needed_pages;

    uint32_t new_region_size = (new_page_index + needed_pages) * page_size;
    while (region_capacity() < new_region_size) {
        grow_region();
    }

    // ptr offsets are "one"-based, so that we can treat 0 as null.
    ptr<page> new_page = ptr<page>((new_page_index + 1) * page_size);
    new_page->zone = zone;
    new_page->previous = nullptr;
    new_page->total = (needed_size + page_mask) & page_alignment;
    new_page->in_use = sizeof(page);
    unlock();
    return new_page;
}

// TO BE AUDITED
void table::dealloc_page_locked(ptr<page> page) OG_NOEXCEPT {
    int32_t total_bytes = page.get(_data_base)->total;
    int32_t num_pages = total_bytes / page_size;
    _used_pages_num -= num_pages;
    if (total_bytes < page_size) {
        return;
    }
    // convert the page address (starts at 512) to an index (starts at 0)
    int32_t page_index = (page / page_size) - 1;
    for (int32_t i = 0; i != num_pages; i += 1) {

        int32_t next_page_index = page_index + i;
        int32_t next_map_index = next_page_index / pages_per_map;

        _page_maps[next_map_index].reset(next_page_index % pages_per_map);
        if (i == 0) {
            _page_metadata_maps[next_map_index].reset(next_page_index % pages_per_map);
        }

        if (_page_maps[next_map_index].none()) {
            make_pages_reusable(next_page_index, true);
        }
    }
}

OG_CONSTEXPR
uint64_t table::raw_page_seed(ptr<page> page) const OG_NOEXCEPT {
    assert_valid(page);
    lock();
    uint32_t page_index = page.page_index();
    uint32_t map_index = page_index / pages_per_map;
    uint64_t result = 0;
    uint32_t w21 = 0;
    uint32_t w22 = 0;
    // FIXME
    if (map_index < _page_metadata_maps.size() && _page_metadata_maps[map_index].test(page_index % page_size)) {
        auto info = page->zone->info();
        // FIXME
        w22 = info.value() & 0xffffff00;
        w21 = info.value() & 0x000000ff;
        result = uint64_t(1) << 32;
    }
    unlock();
    return result || uint64_t(w22 || w21);
}

void table::print() const OG_NOEXCEPT {
    lock();
    fprintf(stderr, "data::table %p:\n  %.2fKB allocated, %.2fKB used, %.2fKB reusable.\n",
            this,
            double(region_capacity() - page_size) / 1024.0,
            double(this->used_pages_num()) / 1024.0,
            double(reusable_pages_num()) / 1024.0);
    unlock();
}

} /* data */
} /* OG */

// AG::data::table::malloc_zone_deleter
