//
//  OGAttributeTypeFlags.h
//  OpenGraphCxx

#ifndef OGAttributeTypeFlags_h
#define OGAttributeTypeFlags_h

#include <OpenGraph/OGBase.h>

typedef OG_OPTIONS(uint32_t, OGAttributeTypeFlags) {
    OGAttributeTypeFlagsComparisonModeBitwise = 0,
    OGAttributeTypeFlagsComparisonModeIndirect = 1,
    OGAttributeTypeFlagsComparisonModeEquatableUnlessPOD = 2,
    OGAttributeTypeFlagsComparisonModeEquatableAlways = 3,
    OGAttributeTypeFlagsComparisonModeMask = 0x03,

    OGAttributeTypeFlagsHasDestroySelf = 1 << 2,
    OGAttributeTypeFlagsMainThread = 1 << 3,
    OGAttributeTypeFlagsExternal = 1 << 4,
    OGAttributeTypeFlagsAsyncThread = 1 << 5,
} OG_SWIFT_NAME(Flags);

#endif /* OGAttributeTypeFlags_h */

