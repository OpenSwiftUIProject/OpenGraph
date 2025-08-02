//
//  OGValueOptions.h
//  OpenGraph_SPI

#ifndef OGValueOptions_h
#define OGValueOptions_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGValueOptions) {
    OGValueOptionsNone = 0,
    OGValueOptionsInputOptionsMask = 0x03,

    OGValueOptionsIncrementGraphVersion = 1 << 2, // AsTopLevelOutput
};

#endif /* OGValueOptions_h */
