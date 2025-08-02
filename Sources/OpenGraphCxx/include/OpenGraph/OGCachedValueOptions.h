//
//  OGCachedValueOptions.h
//  OpenGraphCxx

#ifndef OGCachedValueOptions_h
#define OGCachedValueOptions_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGCachedValueOptions) {
    OGCachedValueOptions_0 = 0,
    OGCachedValueOptions_1 = 1 << 0,
    OGCachedValueOptions_2 = 1 << 1,
    OGCachedValueOptions_4 = 1 << 2,
    OGCachedValueOptions_8 = 1 << 3,
    OGCachedValueOptions_16 = 1 << 4,
};

#endif /* OGCachedValueOptions_h */

