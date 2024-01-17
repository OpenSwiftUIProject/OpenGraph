//
//  wrap_iter.hpp
//
//
//  Created by Kyle on 2024/1/17.
//

#ifndef wrap_iter_hpp
#define wrap_iter_hpp

#include <stdio.h>
#include <vector>

namespace OG {
template <typename ValueType, uint32_t stack_buffer_size, typename SizeType>
class vector;

namespace details {

// LLVM-Project wrap_iter.h
// release/17.0.6 + 6009708b4367171ccdbf4b5905cb6a803753fe18

// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

template <class _Iter>
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename std::iterator_traits<iterator_type>::value_type        value_type;
    typedef typename std::iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename std::iterator_traits<iterator_type>::pointer           pointer;
    typedef typename std::iterator_traits<iterator_type>::reference         reference;
    typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
#if _LIBCPP_STD_VER >= 20
    typedef contiguous_iterator_tag                                    iterator_concept;
#endif

private:
    iterator_type __i_;
public:
    OG_CONSTEXPR __wrap_iter() OG_NOEXCEPT
                : __i_()
    {
    }
    template <class _Up> OG_CONSTEXPR
        __wrap_iter(const __wrap_iter<_Up>& __u,
            typename std::enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = nullptr) OG_NOEXCEPT
            : __i_(__u.base())
    {
    }
    OG_CONSTEXPR reference operator*() const OG_NOEXCEPT
    {
        return *__i_;
    }
    OG_CONSTEXPR pointer operator->() const OG_NOEXCEPT
    {
        return std::__to_address(__i_);
    }
    OG_CONSTEXPR __wrap_iter& operator++() OG_NOEXCEPT
    {
        ++__i_;
        return *this;
    }
    OG_CONSTEXPR __wrap_iter  operator++(int) OG_NOEXCEPT
        {__wrap_iter __tmp(*this); ++(*this); return __tmp;}

    OG_CONSTEXPR __wrap_iter& operator--() OG_NOEXCEPT
    {
        --__i_;
        return *this;
    }
    OG_CONSTEXPR __wrap_iter  operator--(int) OG_NOEXCEPT
        {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    OG_CONSTEXPR __wrap_iter  operator+ (difference_type __n) const OG_NOEXCEPT
        {__wrap_iter __w(*this); __w += __n; return __w;}
    OG_CONSTEXPR __wrap_iter& operator+=(difference_type __n) OG_NOEXCEPT
    {
        __i_ += __n;
        return *this;
    }
    OG_CONSTEXPR __wrap_iter  operator- (difference_type __n) const OG_NOEXCEPT
        {return *this + (-__n);}
    OG_CONSTEXPR __wrap_iter& operator-=(difference_type __n) OG_NOEXCEPT
        {*this += -__n; return *this;}
    OG_CONSTEXPR reference    operator[](difference_type __n) const OG_NOEXCEPT
    {
        return __i_[__n];
    }

    OG_CONSTEXPR iterator_type base() const OG_NOEXCEPT {return __i_;}

private:
    OG_CONSTEXPR
    explicit __wrap_iter(iterator_type __x) OG_NOEXCEPT : __i_(__x)
    {
    }

    template <class _Up> friend class __wrap_iter;
    template <typename ValueType, uint32_t stack_buffer_size, typename SizeType>
    friend class OG::vector;
};

template <class _Iter1>
OG_CONSTEXPR
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return __x.base() == __y.base();
}

template <class _Iter1>
OG_CONSTEXPR
bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1>
OG_CONSTEXPR
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1>
OG_CONSTEXPR
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1>
OG_CONSTEXPR
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1>
OG_CONSTEXPR
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) OG_NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
OG_CONSTEXPR
#ifndef _LIBCPP_CXX03_LANG
auto operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
    -> decltype(__x.base() - __y.base())
#else
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) OG_NOEXCEPT
#endif // C++03
{
    return __x.base() - __y.base();
}

template <class _Iter1>
OG_CONSTEXPR
__wrap_iter<_Iter1> operator+(typename __wrap_iter<_Iter1>::difference_type __n, __wrap_iter<_Iter1> __x) OG_NOEXCEPT
{
    __x += __n;
    return __x;
}
} /* detail */
} /* OG */

namespace std {
template <class _It>
struct std::pointer_traits<OG::details::__wrap_iter<_It> >
{
    typedef OG::details::__wrap_iter<_It> pointer;
    typedef typename pointer_traits<_It>::element_type element_type;
    typedef typename pointer_traits<_It>::difference_type difference_type;

    OG_CONSTEXPR
    static element_type *to_address(pointer __w) OG_NOEXCEPT {
        return std::__to_address(__w.base());
    }
};
} /* std */
#endif /* wrap_iter_hpp */
