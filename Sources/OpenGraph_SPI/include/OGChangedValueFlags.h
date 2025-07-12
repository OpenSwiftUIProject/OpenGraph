//
//  OGChangedValueFlags.h
//  OpenGraph_SPI

#ifndef OGChangedValueFlags_h
#define OGChangedValueFlags_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGChangedValueFlags) {
    OGChangedValueFlagsChanged = 1 << 0,
    OGChangedValueFlagsRequiresMainThread = 1 << 1,
};

#endif /* OGChangedValueFlags_h */
