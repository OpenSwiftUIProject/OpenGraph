//
//  vector.cpp
//  
//
//  Created by Kyle on 2024/1/17.
//

#include "vector.hpp"

template <class _Tp, uint32_t size, class _SizeType>
constexpr inline void
OG::vector<_Tp, size, _SizeType>::push_back(const_reference __x)
{
    // TODO
}

template <class _Tp, uint32_t size, class _SizeType>
constexpr inline void
OG::vector<_Tp, size, _SizeType>::push_back(value_type&& __x)
{
    // TODO
}

template <class _Tp, uint32_t size, class _SizeType>
constexpr inline void
OG::vector<_Tp, size, _SizeType>::pop_back()
{
    // TODO
}

//template <class _Tp, uint32_t size, class _SizeType>
//constexpr inline
//const_iterator OG::vector<_Tp, size, _SizeType>::begin() const noexcept
//{
//}

//template <class _Tp, uint32_t size, class _SizeType>
//constexpr inline
//const_iterator OG::vector<_Tp, size, _SizeType>::end() const noexcept
//{
//}


template <class _Tp, class _SizeType>
constexpr inline void
OG::vector<_Tp, 0, _SizeType>::push_back(const_reference __x)
{
    // TODO
}

template <class _Tp, class _SizeType>
constexpr inline void
OG::vector<_Tp, 0, _SizeType>::push_back(value_type&& __x)
{
    // TODO
}

template <class _Tp, class _SizeType>
constexpr inline void
OG::vector<_Tp, 0, _SizeType>::pop_back()
{
    // TODO
}

//template <class _Tp, class _SizeType>
//constexpr inline
//const_iterator OG::vector<_Tp, 0, _SizeType>::begin() const noexcept
//{
//}

//template <class _Tp, class _SizeType>
//constexpr inline
//const_iterator OG::vector<_Tp, 0, _SizeType>::end() const noexcept
//{
//}
