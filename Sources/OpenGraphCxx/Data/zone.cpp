//
//  zone.cpp
//  OpenGraphCxx

#include "zone.hpp"
#include <OpenGraphCxx/table.hpp>
#include "page.hpp"
#include "../Util/assert.hpp"
#if OG_TARGET_OS_DARWIN
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

namespace OG {
namespace data {

void zone::clear() OG_NOEXCEPT {
    shared_table().lock();
    while (last_page()) {
        auto page = last_page();
        _last_page = page->previous;
        shared_table().dealloc_page_locked(page);
    }
    shared_table().unlock();
}

ptr<void> zone::alloc_slow(uint32_t size, uint32_t alignment_mask) OG_NOEXCEPT {
    if (last_page()) {
        // check if we can use remaining bytes in this page
        ptr<void> next_bytes = last_page() + last_page()->in_use;
        if (next_bytes.page_ptr() == _last_page) {
            ptr<bytes_info> aligned_next_bytes = next_bytes.aligned<bytes_info>();
            int32_t remaining_size = _last_page->total - _last_page->in_use + (next_bytes - aligned_next_bytes);
            if (remaining_size >= sizeof(bytes_info)) {
                bytes_info *remaining_bytes = aligned_next_bytes.get();
                remaining_bytes->next = _free_bytes;
                remaining_bytes->size = remaining_size;
                _free_bytes = aligned_next_bytes;
            }

            // consume this entire page
            _last_page->in_use = _last_page->total;
        }
    }

    ptr<page> new_page;
    if (size <= page_size / 2) {
        new_page = shared_table().alloc_page(this, page_size);
        new_page->previous = _last_page;
        _last_page = new_page;
    } else {
        uint32_t aligned_size = ((sizeof(page) + size) + alignment_mask) & ~alignment_mask;
        new_page = shared_table().alloc_page(this, aligned_size);
        if (_last_page) {
            // It's less likely we will be able to alloc unused bytes from this page,
            // so insert it before the last page.
            new_page->previous = _last_page->previous;
            _last_page->previous = new_page;
        } else {
            _last_page = new_page;
        }
    }

    int32_t aligned_used_bytes = (new_page->in_use + alignment_mask) & ~alignment_mask;

    // Sanity check
    if (aligned_used_bytes + size > new_page->total) {
        precondition_failure("internal error");
    }

    new_page->in_use = aligned_used_bytes + size;
    return new_page + aligned_used_bytes;
};

void zone::print() const OG_NOEXCEPT {
    unsigned long num_pages = 0;
    double pages_total_kb = 0.0;
    double pages_in_use_kb = 0.0;
    if (_last_page) {
        int64_t pages_total = 0;
        int64_t pages_in_use = 0;
        for (auto page = _last_page; page; page = page->previous) {
            num_pages++;
            pages_total += page->total;
            pages_in_use += page->in_use;
        }
        pages_total_kb = pages_total / 1024.0;
        pages_in_use_kb = pages_in_use / 1024.0;
    }

    unsigned long num_free_elements = 0;
    unsigned long free_bytes = 0;
    if (_free_bytes) {
        for (auto bytes = _free_bytes; bytes; bytes = bytes->next) {
            num_free_elements++;
            free_bytes += bytes->size;
        }
    }

    unsigned long num_persistent_buffers = _malloc_buffers.size();
    size_t malloc_total_size = 0;
    for (auto &element : _malloc_buffers) {
        #if OG_TARGET_OS_DARWIN
        malloc_total_size += malloc_size(element.get());
        #else
        malloc_total_size += malloc_usable_size(element.get());
        #endif
    }
    double malloc_total_size_kb = malloc_total_size / 1024.0;

    fprintf(stderr, "%-16p %6lu %8.2f %8.2f    %6lu %6lu     %6lu %8.2f\n",
            this,                   // zone ptr
            num_pages,              // pages
            pages_total_kb,         // total
            pages_in_use_kb,        // in-use
            num_free_elements,      // free
            free_bytes,             // bytes
            num_persistent_buffers, // malloc
            malloc_total_size_kb    // total
    );
}

void zone::print_header() OG_NOEXCEPT {
    fprintf(stderr, "Zones\n%-16s %6s %8s %8s    %6s %6s     %6s %8s\n",
            "zone ptr", "pages", "total", "in-use", "free", "bytes", "malloc", "total");
}

} /* data */
} /* OG */
