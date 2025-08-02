//
//  env.hpp
//  
//
//  Created by Kyle on 2024/4/4.
//

#ifndef env_hpp
#define env_hpp

#include <OpenGraph/OGBase.h>

namespace OG {
OG_INLINE
int get_env(const char *name) {
    char *value = getenv(name);
    if (value) {
        return atoi(value);
    } else {
        return 0;
    }
}
}

#endif /* env_hpp */
