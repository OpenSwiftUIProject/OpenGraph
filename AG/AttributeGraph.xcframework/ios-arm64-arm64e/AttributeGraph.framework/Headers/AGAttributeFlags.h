//
//  AGAttributeFlags.h
//
//
//  Created by Kyle on 2024/2/16.
//

#ifndef AGAttributeFlags_h
#define AGAttributeFlags_h

#include "AGBase.h"

typedef AG_OPTIONS(uint32_t, AGAttributeFlags) {
    AGAttributeFlags_0 = 0,
    AGAttributeFlags_1 = 1 << 0,
    AGAttributeFlags_2 = 1 << 1,
    AGAttributeFlags_4 = 1 << 2,
    AGAttributeFlags_8 = 1 << 3,
    AGAttributeFlags_16 = 1 << 4,
};

#endif /* AGAttributeFlags_h */
