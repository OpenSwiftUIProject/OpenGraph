//
//  OGInputOptions.h
//  OpenGraph_SPI

#ifndef OGInputOptions_h
#define OGInputOptions_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGInputOptions) {
    OGInputOptionsNone = 0,
    OGInputOptionsUnprefetched = 1 << 0,
    OGInputOptionsSyncMainRef = 1 << 1,
};

#endif /* OGInputOptions_h */
