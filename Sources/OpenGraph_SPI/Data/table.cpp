//
//  table.cpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#include "table.hpp"
#include "page.hpp"
#include "page.hpp"
#include "../Util/assert.hpp"
#include <sys/mman.h>
#include <malloc/malloc.h>
#include <mach/mach.h>

void *OGGraphVMRegionBaseAddress;

namespace OG {
namespace data {

malloc_zone_t *_Nullable _malloc_zone;

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
    if (_malloc_zone == nullptr) {
        malloc_zone_t *zone = malloc_create_zone(0, 0);
        _malloc_zone = zone;
        malloc_set_zone_name(zone, "OpenGraph graph data");
    }
}

void table::grow_region() OG_NOEXCEPT {
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
}

void table::make_pages_reusable(uint32_t page_index, bool flag) OG_NOEXCEPT {
    precondition_failure("TODO");
}

ptr<page> table::alloc_page(zone *zone, uint32_t size) OG_NOEXCEPT {
    precondition_failure("TODO");
}

void table::dealloc_page_locked(ptr<page> page) OG_NOEXCEPT {
    precondition_failure("TODO");
}

uint64_t table::raw_page_seed(ptr<page> page) OG_NOEXCEPT {
    precondition_failure("TODO");
//    page.assert_valid();
//
//    lock();
//
//    uint32_t page_index = (page / page_size) - 1;
//    uint32_t map_index = page_index / pages_per_map;
//
//    uint64_t result = 0;
//    if (map_index < _page_metadata_maps.size() && _page_metadata_maps[map_index].test(page_index % page_size)) {
//        auto raw_zone_info = page->zone->info().to_raw_value();
//        result = raw_zone_info | (1 < 8);
//    }
//
//    unlock();
//
//    return result;
}

void table::print() const OG_NOEXCEPT {
    os_unfair_lock_lock(&_lock);
    fprintf(stderr, "data::table %p:\n  %.2fKB allocated, %.2fKB used, %.2fKB reusable.\n",
            this,
            double(_region_capacity - page_size) / 1024.0,
            double(this->used_pages_num()) / 1024.0,
            double(_reusable_pages_num) / 1024.0);
    os_unfair_lock_unlock(&_lock);
}

} /* data */
} /* OG */

// AG::data::table::malloc_zone_deleter
