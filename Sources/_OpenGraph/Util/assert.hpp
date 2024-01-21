//
//  assert.hpp
//  
//
//  Created by Kyle on 2024/1/21.
//

#ifndef assert_hpp
#define assert_hpp

#include "OGBase.hpp"

namespace OG {
void precondition_failure(const char *format, ...) __cold __dead2;
void non_fatal_precondition_failure(const char *format, ...);
} /* OG */

#endif /* assert_hpp */
