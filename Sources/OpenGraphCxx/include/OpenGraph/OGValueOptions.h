//
//  OGValueOptions.h
//  OpenGraphCxx

#ifndef OGValueOptions_h
#define OGValueOptions_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGValueOptions) {
    OGValueOptionsNone = 0,
    OGValueOptionsInputOptionsUnprefetched = 1 << 0,
    OGValueOptionsInputOptionsSyncMainRef = 1 << 1,
    OGValueOptionsInputOptionsMask = 0x03,

    OGValueOptionsIncrementGraphVersion = 1 << 2, // AsTopLevelOutput
};

#endif /* OGValueOptions_h */
