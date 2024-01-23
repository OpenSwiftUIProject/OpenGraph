//
//  OGAttributeTypeFlags.hpp
//
//
//  Created by Kyle on 2023/9/25.
//

#ifndef OGAttributeTypeFlags_hpp
#define OGAttributeTypeFlags_hpp

#include "OGBase.hpp"

typedef OG_OPTIONS(uint32_t, OGAttributeTypeFlags) {
    OGAttributeTypeFlags_0 = 0,
    OGAttributeTypeFlags_1 = 1 << 0,
    OGAttributeTypeFlags_2 = 1 << 1,
    OGAttributeTypeFlags_4 = 1 << 2,
    OGAttributeTypeFlags_8 = 1 << 3,
};

#endif /* OGAttribute_hpp */

