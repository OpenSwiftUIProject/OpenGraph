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
    OGAttributeFlagsDefault = 0,
    OGAttributeFlags_1 = 1 << 0,
    OGAttributeFlagsRemovable = 1 << 1,
    OGAttributeFlagsInvalidatable = 1 << 2,
};

#endif /* OGAttributeFlags_h */
