//
//  page.hpp
//  OpenGraphCxx

#ifndef page_hpp
#define page_hpp

#include "OGBase.h"
#include "ptr.hpp"

namespace OG {
namespace data {

class zone;
template <typename T> class ptr;

struct page {
    zone *zone;
    ptr<page> previous;
    uint32_t total;
    uint32_t in_use;
}; /* page */

} /* data */
} /* OG */

#endif /* page_hpp */
