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
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter() _NOEXCEPT
                : __i_()
    {
    }
    template <class _Up> _LIBCPP_CONSTEXPR_SINCE_CXX14
        __wrap_iter(const __wrap_iter<_Up>& __u,
            typename std::enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = nullptr) _NOEXCEPT
            : __i_(__u.base())
    {
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 reference operator*() const _NOEXCEPT
    {
        return *__i_;
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 pointer operator->() const _NOEXCEPT
    {
        return _VSTD::__to_address(__i_);
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator++() _NOEXCEPT
    {
        ++__i_;
        return *this;
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter  operator++(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); ++(*this); return __tmp;}

    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator--() _NOEXCEPT
    {
        --__i_;
        return *this;
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter  operator--(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter  operator+ (difference_type __n) const _NOEXCEPT
        {__wrap_iter __w(*this); __w += __n; return __w;}
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator+=(difference_type __n) _NOEXCEPT
    {
        __i_ += __n;
        return *this;
    }
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter  operator- (difference_type __n) const _NOEXCEPT
        {return *this + (-__n);}
    _LIBCPP_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator-=(difference_type __n) _NOEXCEPT
        {*this += -__n; return *this;}
    _LIBCPP_CONSTEXPR_SINCE_CXX14 reference    operator[](difference_type __n) const _NOEXCEPT
    {
        return __i_[__n];
    }

    _LIBCPP_CONSTEXPR_SINCE_CXX14 iterator_type base() const _NOEXCEPT {return __i_;}

private:
    _LIBCPP_CONSTEXPR_SINCE_CXX14
    explicit __wrap_iter(iterator_type __x) _NOEXCEPT : __i_(__x)
    {
    }

    template <class _Up> friend class __wrap_iter;
    template <typename ValueType, uint32_t stack_buffer_size, typename SizeType>
    friend class _LIBCPP_TEMPLATE_VIS OG::vector;
};

template <class _Iter1>
_LIBCPP_CONSTEXPR
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() == __y.base();
}

template <class _Iter1>
_LIBCPP_CONSTEXPR_SINCE_CXX14
bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR_SINCE_CXX14
bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1>
_LIBCPP_CONSTEXPR
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR
bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1>
_LIBCPP_CONSTEXPR
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR
bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1>
_LIBCPP_CONSTEXPR
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR
bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1>
_LIBCPP_CONSTEXPR
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR
bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
_LIBCPP_CONSTEXPR_SINCE_CXX14
#ifndef _LIBCPP_CXX03_LANG
auto operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
    -> decltype(__x.base() - __y.base())
#else
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
#endif // C++03
{
    return __x.base() - __y.base();
}

template <class _Iter1>
_LIBCPP_CONSTEXPR_SINCE_CXX14
__wrap_iter<_Iter1> operator+(typename __wrap_iter<_Iter1>::difference_type __n, __wrap_iter<_Iter1> __x) _NOEXCEPT
{
    __x += __n;
    return __x;
}
} /* detail */
} /* OG */

namespace std {
template <class _It>
struct _LIBCPP_TEMPLATE_VIS std::pointer_traits<OG::details::__wrap_iter<_It> >
{
    typedef OG::details::__wrap_iter<_It> pointer;
    typedef typename pointer_traits<_It>::element_type element_type;
    typedef typename pointer_traits<_It>::difference_type difference_type;

    _LIBCPP_CONSTEXPR
    static element_type *to_address(pointer __w) _NOEXCEPT {
        return _VSTD::__to_address(__w.base());
    }
};
} /* std */
#endif /* wrap_iter_hpp */
