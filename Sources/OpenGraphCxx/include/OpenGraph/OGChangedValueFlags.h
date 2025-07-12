//
//  OGChangedValueFlags.h
//  OpenGraphCxx

#ifndef OGChangedValueFlags_h
#define OGChangedValueFlags_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGChangedValueFlags) {
    OGChangedValueFlagsChanged = 1 << 0,
    OGChangedValueFlagsRequiresMainThread = 1 << 1,
};

#endif /* OGChangedValueFlags_h */
