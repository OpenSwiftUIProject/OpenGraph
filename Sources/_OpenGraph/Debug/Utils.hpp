//
//  Utils.hpp
//  
//
//  Created by Kyle on 2024/1/15.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <OpenFoundation/OpenFoundation.h>
#include <cstdio>

OF_ASSUME_NONNULL_BEGIN

namespace OG {
namespace details {
template <typename T, size_t Alignment>
void *_Nullable realloc_vector(void* ptr, T& size, T new_size);

template <typename T, size_t Alignment>
void *_Nullable realloc_vector(void* src, void* dst, T dstSize, T& size, T newSize);
}
}

OF_ASSUME_NONNULL_END

#endif /* Utils_hpp */
