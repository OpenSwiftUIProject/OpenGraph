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
    AGAttributeFlagsDefault = 0,
    AGAttributeFlags_1 = 1 << 0,
    AGAttributeFlagsRemovable = 1 << 1,
    AGAttributeFlagsInvalidatable = 1 << 2,
};

#endif /* AGAttributeFlags_h */
