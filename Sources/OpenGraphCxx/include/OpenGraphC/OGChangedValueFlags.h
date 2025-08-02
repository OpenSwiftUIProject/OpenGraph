//
//  OGChangedValueFlags.h
//  OpenGraphCxx

#ifndef OGChangedValueFlags_h
#define OGChangedValueFlags_h

#include <OpenGraphC/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGChangedValueFlags) {
    OGChangedValueFlags_1 = 1 << 0,
    OGChangedValueFlagsRequiresMainThread = 1 << 1,
};

#endif /* OGChangedValueFlags_h */
