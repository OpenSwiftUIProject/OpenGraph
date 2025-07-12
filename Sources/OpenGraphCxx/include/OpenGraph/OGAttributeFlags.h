//
//  OGAttributeFlags.h
//  OpenGraphCxx
//
//  Audited for RELEASE_2021
//  Status: Complete

#ifndef OGAttributeFlags_h
#define OGAttributeFlags_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint8_t, OGAttributeFlags) {
    OGAttributeFlagsDefault = 0,
    OGAttributeFlagsActive = 1 << 0,
    OGAttributeFlagsRemovable = 1 << 1,
    OGAttributeFlagsInvalidatable = 1 << 2,
    
    OGAttributeFlagsMask = 0xFF,
};

#endif /* OGAttributeFlags_h */
