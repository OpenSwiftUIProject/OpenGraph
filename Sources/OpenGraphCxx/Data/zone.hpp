//
//  zone.hpp
//  OpenGraphCxx

#ifndef zone_hpp
#define zone_hpp

#include "OGBase.h"
#include "ptr.hpp"

namespace OG {
namespace data {

class zone {
public:
    class info {
    private:
        constexpr static uint32_t zone_id_mask = 0x7fffffff;
        uint32_t _value;
        constexpr info(uint32_t value) : _value(value){};

    public:
        uint32_t zone_id() { return _value & zone_id_mask; };
        info with_zone_id(uint32_t zone_id) const { return info((_value & ~zone_id_mask) | (zone_id & zone_id_mask)); };

        uint32_t to_raw_value() { return _value; };
        static info from_raw_value(uint32_t value) { return info(value); };
    }; /* info */
public:
    zone();

    OG_INLINE OG_CONSTEXPR
    ptr<page> last_page() const OG_NOEXCEPT { return _last_page; };

    OG_INLINE OG_CONSTEXPR
    info info() const OG_NOEXCEPT { return _info; };

    void clear() OG_NOEXCEPT;

    ptr<void> alloc_slow(uint32_t size, uint32_t alignment_mask) OG_NOEXCEPT;

    void *alloc_persistent(size_t size) OG_NOEXCEPT;

    void realloc_bytes(ptr<void> *buffer, uint32_t size, uint32_t new_size, uint32_t alignment_mask) OG_NOEXCEPT;

//    ptr<void> alloc_bytes(uint32_t size, uint32_t alignment_mask);
    ptr<void> alloc_bytes_recycle(uint32_t size, uint32_t alignment_mask) OG_NOEXCEPT;

    // Printing
    void print() const OG_NOEXCEPT;

    void print_header() OG_NOEXCEPT;

    ~zone();
private:
    typedef struct _bytes_info {
        ptr<struct _bytes_info> next;
        uint32_t size;
    } bytes_info;

    vector<std::unique_ptr<void, table::malloc_zone_deleter>, 0, uint32_t> _malloc_buffers;
    ptr<page> _last_page;
    ptr<bytes_info> _free_bytes;
    class info _info;
}; /* zone */

} /* data */
} /* OG */

#endif /* zone_hpp */
