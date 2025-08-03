//
//  zone.hpp
//  OpenGraphCxx

#ifndef zone_hpp
#define zone_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraphCxx/Data/ptr.hpp>

namespace OG {
namespace data {

class zone {
public:
    class info {
    public:
        OG_INLINE OG_CONSTEXPR
        info() OG_NOEXCEPT : _value(0) {};

        OG_INLINE OG_CONSTEXPR
        info(uint32_t value) OG_NOEXCEPT : _value(value){};

        OG_INLINE OG_CONSTEXPR
        info(uint32_t zone_id, bool deleted) OG_NOEXCEPT : _value((zone_id & zone_id_mask) | (deleted ? 1 : 0)) {};

        OG_INLINE OG_CONSTEXPR
        uint32_t value() const OG_NOEXCEPT { return _value; };

        OG_INLINE OG_CONSTEXPR
        uint32_t zone_id() const OG_NOEXCEPT { return _value & zone_id_mask; };

        OG_INLINE OG_CONSTEXPR
        bool is_deleted() const OG_NOEXCEPT { return (_value & deleted) != 0; };

        OG_INLINE OG_CONSTEXPR
        info with_zone_id(uint32_t zone_id) const OG_NOEXCEPT {
            return info((_value & ~zone_id_mask) | (zone_id & zone_id_mask), is_deleted());
        };

        OG_INLINE OG_CONSTEXPR
        info with_deleted(bool deleted) const OG_NOEXCEPT {
            return info(zone_id(), deleted);
        }
    private:
        enum : uint32_t {
            zone_id_mask = 0x7fffffff,
            deleted = 0x80000000,
        };
        uint32_t _value;
    }; /* info */
public:
//    zone() OG_NOEXCEPT = default;
//    ~zone() OG_NOEXCEPT;

    OG_INLINE OG_CONSTEXPR
    auto& malloc_buffers() const OG_NOEXCEPT { return _malloc_buffers; };

    OG_INLINE OG_CONSTEXPR
    ptr<page> last_page() const OG_NOEXCEPT { return _last_page; };

    OG_INLINE OG_CONSTEXPR
    info info() const OG_NOEXCEPT { return _info; };

    OG_INLINE
    void clear();

    ptr<void> alloc_slow(uint32_t size, uint32_t alignment_mask) OG_NOEXCEPT;

    void *alloc_persistent(size_t size) OG_NOEXCEPT;

    void realloc_bytes(ptr<void> *buffer, uint32_t size, uint32_t new_size, uint32_t alignment_mask) OG_NOEXCEPT;

//    ptr<void> alloc_bytes(uint32_t size, uint32_t alignment_mask);
    ptr<void> alloc_bytes_recycle(uint32_t size, uint32_t alignment_mask) OG_NOEXCEPT;

    // Printing
    void print() const OG_NOEXCEPT;

    void print_header() const OG_NOEXCEPT;
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
