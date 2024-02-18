//
//  OGAttributeFlags.h
//
//
//  Created by Kyle on 2024/2/16.
//

#ifndef OGAttributeFlags_h
#define OGAttributeFlags_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGAttributeFlags) {
    OGAttributeFlags_0 = 0,
    OGAttributeFlags_1 = 1 << 0,
    OGAttributeFlags_2 = 1 << 1,
    OGAttributeFlags_4 = 1 << 2,
    OGAttributeFlags_8 = 1 << 3,
    OGAttributeFlags_16 = 1 << 4,
};

#endif /* OGAttributeFlags_h */
