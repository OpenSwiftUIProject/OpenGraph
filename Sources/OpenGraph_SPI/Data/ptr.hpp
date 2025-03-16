//
//  ptr.hpp
//  OpenGraph_SPI
//
//  Status: Complete
//  Modified from https://github.com/jcmosc/Compute/blob/0a6b21a4cdeb9bbdd95e7e914c4e18bed37a2456/Sources/ComputeCxx/Data/Pointer.h [MIT License]

#ifndef ptr_hpp
#define ptr_hpp

#include "OGBase.h"
#include "table.hpp"
#include <mach/vm_types.h>
#include <bitset>
#include <os/lock.h>
#include "page.hpp"

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
    ptr(difference_type offset = 0) : _offset(offset){};
    ptr(nullptr_t){};

    void assert_valid() const {
        if (_offset >= table::shared().data_capacity()) {
            precondition_failure("invalid data offset: %u", _offset);
        }
    }

    element_type *_Nonnull get() const noexcept {
        assert(_offset != 0);
        return reinterpret_cast<element_type *>(table::shared().data_base() + _offset);
    }

    ptr<page> page_ptr() const noexcept { return ptr<page>(_offset & page_alignment); }

    difference_type page_relative_offset() const noexcept { return _offset & page_mask; }

    template <typename U> ptr<U> aligned(difference_type alignment_mask = sizeof(difference_type) - 1) const {
        return ptr<U>((_offset + alignment_mask) & ~alignment_mask);
    };

    operator bool() const noexcept { return _offset != 0; };
    std::add_lvalue_reference_t<T> operator*() const noexcept { return *get(); };
    T *_Nonnull operator->() const noexcept { return get(); };

    bool operator==(nullptr_t) const noexcept { return _offset == 0; };
    bool operator!=(nullptr_t) const noexcept { return _offset != 0; };

    bool operator<(difference_type offset) const noexcept { return _offset < offset; };
    bool operator<=(difference_type offset) const noexcept { return _offset <= offset; };
    bool operator>(difference_type offset) const noexcept { return _offset > offset; };
    bool operator>=(difference_type offset) const noexcept { return _offset >= offset; };

    template <typename U> ptr<U> operator+(difference_type shift) const noexcept { return ptr(_offset + shift); };
    template <typename U> ptr<U> operator-(difference_type shift) const noexcept { return ptr(_offset - shift); };

    template <typename U> difference_type operator-(const ptr<U> &other) const noexcept {
        return _offset - other._offset;
    };
}; /* ptr */

} /* data */
} /* OG */

OG_ASSUME_NONNULL_END

#endif /* ptr_hpp */
