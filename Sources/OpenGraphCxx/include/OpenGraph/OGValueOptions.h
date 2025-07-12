//
//  OGValueOptions.h
//  OpenGraphCxx

#ifndef OGValueOptions_h
#define OGValueOptions_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGValueOptions) {
    OGValueOptionsNone = 0,
    OGValueOptionsInputOptionsMask = 0x03,

    OGValueOptionsIncrementGraphVersion = 1 << 2, // AsTopLevelOutput
};

#endif /* OGValueOptions_h */
