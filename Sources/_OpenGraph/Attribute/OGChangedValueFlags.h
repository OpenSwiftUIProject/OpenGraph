//
//  OGChangedValueFlags.h
//
//
//  Created by Kyle on 2024/2/21.
//

#ifndef OGChangedValueFlags_h
#define OGChangedValueFlags_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGChangedValueFlags) {
    OGChangedValueFlags_0 = 0,
    OGChangedValueFlags_1 = 1 << 0,
};

#endif /* OGChangedValueFlags_h */
