//
//  OGGraphCounterQueryType.h
//  OpenGraphCxx

#ifndef OGGraphCounterQueryType_h
#define OGGraphCounterQueryType_h

#include <OpenGraph/OGBase.h>

typedef OG_ENUM(uint32_t, OGGraphCounterQueryType) {
    OGGraphCounterQueryTypeNodes,
    OGGraphCounterQueryTypeTransactions,
    OGGraphCounterQueryTypeUpdates,
    OGGraphCounterQueryTypeChanges,
    OGGraphCounterQueryTypeContextID,
    OGGraphCounterQueryTypeGraphID,
    OGGraphCounterQueryTypeContextThreadUpdating,
    OGGraphCounterQueryTypeThreadUpdating,
    OGGraphCounterQueryTypeContextNeedsUpdate,
    OGGraphCounterQueryTypeNeedsUpdate,
    OGGraphCounterQueryTypeMainThreadUpdates,
    OGGraphCounterQueryTypeCreatedNodes,
    OGGraphCounterQueryTypeSubgraphs,
    OGGraphCounterQueryTypeCreatedSubgraphs,
} OG_SWIFT_NAME(OGGraphRef.CounterQueryType);

#endif /* OGGraphCounterQueryType_h */
