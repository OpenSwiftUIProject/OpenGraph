//
//  AGAttributeFlags.h
//  AttributeGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

#ifndef AGAttributeFlags_h
#define AGAttributeFlags_h

#include "AGBase.h"

typedef AG_OPTIONS(uint32_t, AGAttributeFlags) {
    AGAttributeFlagsDefault = 0,
    AGAttributeFlagsActive = 1 << 0,
    AGAttributeFlagsRemovable = 1 << 1,
    AGAttributeFlagsInvalidatable = 1 << 2,
    
    AGAttributeFlagsMask = 0xFF,
};

#endif /* AGAttributeFlags_h */
