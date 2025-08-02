//
//  ptr.hpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified from https://github.com/jcmosc/Compute/blob/0a6b21a4cdeb9bbdd95e7e914c4e18bed37a2456/Sources/ComputeCxx/Data/Pointer.h [MIT License]

#ifndef ptr_hpp
#define ptr_hpp

#include "OGBase.h"
#include <OpenGraphCxx/Internal/table.hpp>
#include <bitset>
#include "page_const.hpp"

OG_ASSUME_NONNULL_BEGIN

namespace OG {
namespace data {

struct page;

template <typename T> class ptr {
public:
    using element_type = T;
    using difference_type = uint32_t;

private:
    difference_type _offset;

    template <typename U> friend class ptr;

public:
    OG_INLINE OG_CONSTEXPR ptr(difference_type offset = 0) : _offset(offset){};
    OG_INLINE OG_CONSTEXPR ptr(std::nullptr_t){};

    OG_INLINE
    void assert_valid(uint32_t capacity = shared_table().data_capacity()) const {
        if (capacity <= _offset) {
            precondition_failure("invalid data offset: %u", _offset);
        }
    }

    OG_INLINE
    element_type *_Nonnull get(vm_address_t base = shared_table().data_base()) const OG_NOEXCEPT {
        assert(_offset != 0);
        return reinterpret_cast<element_type *>(base + _offset);
    }

    OG_INLINE OG_CONSTEXPR
    ptr<page> page_ptr() const OG_NOEXCEPT { return ptr<page>(_offset & page_alignment); }

    OG_INLINE OG_CONSTEXPR
    uint32_t page_index() const OG_NOEXCEPT { return (_offset >> page_mask_bits) - 1; }

    OG_INLINE OG_CONSTEXPR
    difference_type page_relative_offset() const OG_NOEXCEPT { return _offset & page_mask; }

    template <typename U> ptr<U> aligned(difference_type alignment_mask = sizeof(difference_type) - 1) const {
        return ptr<U>((_offset + alignment_mask) & ~alignment_mask);
    };

    OG_INLINE OG_CONSTEXPR
    operator bool() const OG_NOEXCEPT { return _offset != 0; };

    OG_INLINE OG_CONSTEXPR
    std::add_lvalue_reference_t<T> operator*() const OG_NOEXCEPT { return *get(); };

    OG_INLINE OG_CONSTEXPR
    T *_Nonnull operator->() const OG_NOEXCEPT { return get(); };

    OG_INLINE OG_CONSTEXPR
    bool operator==(std::nullptr_t) const OG_NOEXCEPT { return _offset == 0; };

    OG_INLINE OG_CONSTEXPR
    bool operator!=(std::nullptr_t) const OG_NOEXCEPT { return _offset != 0; };

    OG_INLINE OG_CONSTEXPR
    bool operator<(difference_type offset) const OG_NOEXCEPT { return _offset < offset; };

    OG_INLINE OG_CONSTEXPR
    bool operator<=(difference_type offset) const OG_NOEXCEPT { return _offset <= offset; };

    OG_INLINE OG_CONSTEXPR
    bool operator>(difference_type offset) const OG_NOEXCEPT { return _offset > offset; };

    OG_INLINE OG_CONSTEXPR
    bool operator>=(difference_type offset) const OG_NOEXCEPT { return _offset >= offset; };

    template <typename U>
    OG_INLINE OG_CONSTEXPR
    ptr<U> operator+(difference_type shift) const OG_NOEXCEPT { return ptr(_offset + shift); };

    template <typename U>
    OG_INLINE OG_CONSTEXPR
    ptr<U> operator-(difference_type shift) const OG_NOEXCEPT { return ptr(_offset - shift); };

    template <typename U>
    OG_INLINE OG_CONSTEXPR
    difference_type operator-(const ptr<U> &other) const OG_NOEXCEPT {
        return _offset - other._offset;
    };
}; /* ptr */

} /* data */
} /* OG */

OG_ASSUME_NONNULL_END

#endif /* ptr_hpp */
