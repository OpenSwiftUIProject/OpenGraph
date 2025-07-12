//
//  OGCounterQueryType.h
//  OpenGraphCxx

#ifndef OGCounterQueryType_h
#define OGCounterQueryType_h

#include <OpenGraph/OGBase.h>

typedef OG_ENUM(uint32_t, OGCounterQueryType) {
    OGCounterQueryTypeNodeCount,
    OGCounterQueryTypeTransactionCount,
    OGCounterQueryTypeUpdateCount,
    OGCounterQueryTypeChangeCount,
    OGCounterQueryTypeContextID,
    OGCounterQueryTypeGraphID,
    OGCounterQueryTypeContextThreadUpdating,
    OGCounterQueryTypeThreadUpdating,
    OGCounterQueryTypeContextNeedsUpdate,
    OGCounterQueryTypeNeedsUpdate,
    OGCounterQueryTypeMainThreadUpdateCount,
    OGCounterQueryTypeNodeTotalCount,
    OGCounterQueryTypeSubgraphCount,
    OGCounterQueryTypeSubgraphTotalCount,
};

#endif /* OGCounterQueryType_h */
