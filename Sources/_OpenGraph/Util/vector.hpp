//
//  vector.hpp
//
//
//  Created by Kyle on 2024/1/15.
//

#ifndef vector_hpp
#define vector_hpp

#include "OGBase.hpp"
#include "wrap_iter.hpp"
#include "realloc_vector.hpp"
#include <cstdio>
#include <vector>

namespace OG {
template <class _Tp, uint32_t size, class _SizeType = uint32_t>
class vector final {
private:
    typedef std::allocator<_Tp>                             __default_allocator_type;
public:
    typedef vector                                          __self;
    typedef _Tp                                             value_type;
    typedef __default_allocator_type                        allocator_type;
    typedef std::allocator_traits<allocator_type>           __alloc_traits;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef typename __alloc_traits::size_type              size_type;
    typedef typename __alloc_traits::difference_type        difference_type;
    typedef typename __alloc_traits::pointer                pointer;
    typedef typename __alloc_traits::const_pointer          const_pointer;
    typedef OG::details::__wrap_iter<pointer>               iterator;
    typedef OG::details::__wrap_iter<const_pointer>         const_iterator;
    typedef std::reverse_iterator<iterator>                 reverse_iterator;
    typedef std::reverse_iterator<const_iterator>           const_reverse_iterator;
    
    constexpr void push_back(const_reference __x);
    constexpr void push_back(value_type&& __x);
    constexpr void pop_back();
    
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator end() const noexcept;
    
private:
    // TODO
    static constexpr size_type stack_buffer_byte_size = 0;
    
    uint8_t _stack_buffer[stack_buffer_byte_size] = {0};
    pointer _buffer;
    size_type _count = 0;
    size_type _capacity = 0;
};


template <class _Tp, class _SizeType>
class vector<_Tp, 0, _SizeType> final {
private:
    typedef std::allocator<_Tp>                             __default_allocator_type;
public:
    typedef vector                                          __self;
    typedef _Tp                                             value_type;
    typedef __default_allocator_type                        allocator_type;
    typedef std::allocator_traits<allocator_type>           __alloc_traits;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef typename __alloc_traits::size_type              size_type;
    typedef typename __alloc_traits::difference_type        difference_type;
    typedef typename __alloc_traits::pointer                pointer;
    typedef typename __alloc_traits::const_pointer          const_pointer;
    typedef OG::details::__wrap_iter<pointer>               iterator;
    typedef OG::details::__wrap_iter<const_pointer>         const_iterator;
    typedef std::reverse_iterator<iterator>                 reverse_iterator;
    typedef std::reverse_iterator<const_iterator>           const_reverse_iterator;
    
    constexpr void push_back(const_reference __x);
    constexpr void push_back(value_type&& __x);
    constexpr void pop_back();
    
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator end() const noexcept;
private:
    pointer _buffer = nullptr;
    size_type _count = 0;
    size_type _capacity = 0;
};
}
#endif /* vector_hpp */
