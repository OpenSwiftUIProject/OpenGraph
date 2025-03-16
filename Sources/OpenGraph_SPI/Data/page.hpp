//
//  page.hpp
//  OpenGraph_SPI

#ifndef page_hpp
#define page_hpp

#include "OGBase.h"

namespace OG {
namespace data {

constexpr const uint32_t page_mask_bits = 9;

/// 0x200
constexpr const uint32_t page_size = 1 << page_mask_bits;

/// 0x1FF
constexpr const uint32_t page_mask = page_size - 1;

/// 0xFFFF_FFE0
constexpr const uintptr_t page_alignment = ~page_mask;

class zone;

struct page {
//    zone *zone;
//    ptr<page> previous;
//    uint32_t total;
//    uint32_t in_use;
}; /* page */

} /* data */
} /* OG */

#endif /* page_hpp */
