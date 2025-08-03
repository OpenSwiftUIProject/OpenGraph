//
//  free_deleter.hpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#ifndef OPENGRAPH_CXX_UTIL_FREE_DELETER_HPP
#define OPENGRAPH_CXX_UTIL_FREE_DELETER_HPP

#include <OpenGraph/OGBase.h>

OG_ASSUME_NONNULL_BEGIN

namespace util {

class free_deleter {
public:
    template <typename T> void operator()(T *_Nullable ptr) {
       if (ptr) {
           free((void *)ptr);
       }
    }
}; /* class free_deleter */

} /* namespace util */

OG_ASSUME_NONNULL_END

#endif /* OPENGRAPH_CXX_UTIL_FREE_DELETER_HPP */
