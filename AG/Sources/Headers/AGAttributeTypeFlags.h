//
//  AGAttributeTypeFlags.h
//
//
//  Created by Kyle on 2023/9/25.
//

#ifndef AGAttributeTypeFlags_h
#define AGAttributeTypeFlags_h

#include "AGBase.h"

typedef AG_OPTIONS(uint32_t, AGAttributeTypeFlags) {
    AGAttributeTypeFlags_0 = 0,
    AGAttributeTypeFlags_1 = 1 << 0,
    AGAttributeTypeFlags_2 = 1 << 1,
    AGAttributeTypeFlags_4 = 1 << 2,
    AGAttributeTypeFlags_8 = 1 << 3,
    AGAttributeTypeFlags_16 = 1 << 4,
};

#endif /* AGAttributeTypeFlags_h */

