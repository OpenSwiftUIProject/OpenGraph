//
//  table.cpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0

#include "table.hpp"

// FIXME: Will this be mangled by C++? TO BE VERIFIED
static void *OGGraphVMRegionBaseAddress;

namespace OG {
namespace data {

table _shared_table_bytes;

table &table::ensure_shared() {
    static dispatch_once_t once;
    dispatch_once_f(&once, nullptr, [](void *_Nullable context){
        // FIXME: TO BE VERIFIED? Any diff here
        // new (&_shared_table_bytes) table();
        _shared_table_bytes = table();
    });
    return _shared_table_bytes;
}

table &table::shared() { return _shared_table_bytes; }

table::table() {
//    constexpr vm_size_t initial_size = 32 * pages_per_map * page_size;
//
//    void *region = mmap(nullptr, initial_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
//    if (region == MAP_FAILED) {
//        precondition_failure("memory allocation failure (%u bytes, %u)", initial_size, errno);
//    }
//
//    _vm_region_base_address = reinterpret_cast<vm_address_t>(region);
//    _vm_region_size = initial_size;
//
//    AGGraphVMRegionBaseAddress = region;
//
//    _ptr_base = reinterpret_cast<vm_address_t>(region) - page_size;
//    _ptr_max_offset = initial_size + page_size;
//
//    if (!_malloc_zone) {
//        _malloc_zone = malloc_create_zone(0, 0);
//        malloc_set_zone_name(_malloc_zone, "Compute graph data");
//    }
}

void table::print() const {
    fprintf(stderr, "data::table %p:\\n  %.2fKB allocated, %.2fKB used, %.2fKB reusable.\\n");
}

} /* data */
} /* OG */

// _AGGraphVMRegionBaseAddress:
// AG::data::_shared_table_bytes
// AG::data::table::_malloc_zone
// AG::data::table::malloc_zone_deleter
