//
//  realloc_vector.cpp
//  
//
//  Created by Kyle on 2024/1/17.
//

#include "realloc_vector.hpp"
#include "assert.hpp"

#if TARGET_OS_DARWIN
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif /* TARGET_OS_DARWIN */

template <typename T, size_t Alignment>
void *_Nullable OG::details::realloc_vector(void* ptr, T& size, T new_size) {
    if (new_size == 0) {
        size = 0;
        free(ptr);
        return nullptr;
    } else {
        size_t msize = malloc_good_size(new_size * Alignment);
        if (size == msize / Alignment) {
            return ptr;
        } else {
            void *new_ptr = realloc(ptr, msize);
            if (new_ptr == nullptr) {
                OG::precondition_failure("memory allocation failed");
            } else {
                size = msize / Alignment;
                return new_ptr;
            }
        }
    }
}

template <typename T, size_t Alignment>
void *_Nullable OG::details::realloc_vector(void* src, void* dst, T dstSize, T& size, T newSize) {
    if (newSize < dstSize) {
        if (src == dst) {
            return src;
        } else {
            memcpy(dst, src, newSize * Alignment);
            size = dstSize;
            free(src);
            return dst;
        }
    } else {
        size_t msize = malloc_good_size(newSize * Alignment);
        if (size == msize / Alignment) {
            return src;
        } else {
            if (src == dst) {
                void *new_ptr = malloc(msize);
                if (new_ptr == nullptr) {
                    OG::precondition_failure("memory allocation failed");
                } else {
                    memcpy(new_ptr, src, size * Alignment);
                    size = msize / Alignment;
                    return new_ptr;
                }
            } else {
                void *new_ptr = realloc(src, msize);
                if (new_ptr == nullptr) {
                    OG::precondition_failure("memory allocation failed");
                } else {
                    size = msize / Alignment;
                    return new_ptr;
                }
            }
        }
    }
}
