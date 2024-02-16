//
//  AGAttributeTypeFlags.hpp
//
//
//  Created by Kyle on 2023/9/25.
//

#ifndef AGAttributeTypeFlags_hpp
#define AGAttributeTypeFlags_hpp

#include "AGBase.hpp"

typedef AG_OPTIONS(uint32_t, AGAttributeTypeFlags) {
    AGAttributeTypeFlags_0 = 0,
    AGAttributeTypeFlags_1 = 1 << 0,
    AGAttributeTypeFlags_2 = 1 << 1,
    AGAttributeTypeFlags_4 = 1 << 2,
    AGAttributeTypeFlags_8 = 1 << 3,
};

#endif /* AGAttribute_hpp */

