//
//  OGAttributeTypeFlags.h
//  OpenGraphCxx

#ifndef OGAttributeTypeFlags_h
#define OGAttributeTypeFlags_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGAttributeTypeFlags) {
    OGAttributeTypeFlagsDefault = 0,
    OGAttributeTypeFlags_1 = 1 << 0,
    OGAttributeTypeFlags_2 = 1 << 1,
    OGAttributeTypeFlags_4 = 1 << 2,
    OGAttributeTypeFlagsMainThread = 1 << 3,
    OGAttributeTypeFlags_16 = 1 << 4,
    OGAttributeTypeFlagsAsyncThread = 1 << 5,
};

#endif /* OGAttributeTypeFlags_h */

