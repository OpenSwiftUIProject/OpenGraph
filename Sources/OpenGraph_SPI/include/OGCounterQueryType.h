//
//  OGCounterQueryType.h
//  OpenGraph_SPI

#ifndef OGCounterQueryType_h
#define OGCounterQueryType_h

#include "OGBase.h"

typedef OG_ENUM(uint32_t, OGCounterQueryType) {
    OGCounterQueryTypeNodes,
    OGCounterQueryTypeTransactions,
    OGCounterQueryTypeUpdates,
    OGCounterQueryTypeChanges,
    OGCounterQueryTypeContextID,
    OGCounterQueryTypeGraphID,
    OGCounterQueryTypeContextThreadUpdating,
    OGCounterQueryTypeThreadUpdating,
    OGCounterQueryTypeContextNeedsUpdate,
    OGCounterQueryTypeNeedsUpdate,
    OGCounterQueryTypeMainThreadUpdates,
    OGCounterQueryTypeCreatedNodes,
    OGCounterQueryTypeSubgraphs,
    OGCounterQueryTypeCreatedSubgraphs,
} OG_SWIFT_NAME(OGGraphRef.CounterQueryType);

#endif /* OGCounterQueryType_h */
