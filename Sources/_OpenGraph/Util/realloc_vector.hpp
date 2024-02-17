//
//  realloc_vector.hpp
//  
//
//  Created by Kyle on 2024/1/17.
//

#ifndef realloc_vector_hpp
#define realloc_vector_hpp

#include "OGBase.h"
#include <stdio.h>

OG_ASSUME_NONNULL_BEGIN

namespace OG {
namespace details {
template <typename T = uint32_t, size_t Alignment>
void *_Nullable realloc_vector(void* ptr, T& size, T new_size);

template <typename T = uint32_t, size_t Alignment>
void *_Nullable realloc_vector(void* src, void* dst, T dstSize, T& size, T newSize);
} /* details */
} /* OG */

OG_ASSUME_NONNULL_END

#endif /* realloc_vector_hpp */
