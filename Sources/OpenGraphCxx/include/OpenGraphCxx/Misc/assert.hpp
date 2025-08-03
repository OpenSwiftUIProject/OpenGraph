//
//  assert.hpp
//  OpenGraphCxx

#ifndef assert_hpp
#define assert_hpp

#include <OpenGraph/OGBase.h>

namespace OG {
void precondition_failure(const char *format, ...) __cold __dead2;
void non_fatal_precondition_failure(const char *format, ...);
} /* OG */

#endif /* assert_hpp */
