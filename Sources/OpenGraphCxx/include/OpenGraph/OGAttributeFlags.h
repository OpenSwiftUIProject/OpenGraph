//
//  OGAttributeFlags.h
//  OpenGraphCxx
//
//  Audited for RELEASE_2021
//  Status: Complete

#ifndef OGAttributeFlags_h
#define OGAttributeFlags_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>

typedef OG_OPTIONS(uint8_t, OGAttributeFlags) {
    OGAttributeFlagsNone = 0,
    OGAttributeFlagsAll = 0xFF,
} OG_SWIFT_NAME(OGSubgraphRef.Flags);

#endif /* OGAttributeFlags_h */
