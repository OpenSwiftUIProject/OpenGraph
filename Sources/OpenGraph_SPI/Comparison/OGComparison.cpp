//
//  OGCompareValues.cpp
//  OpenGraph_SPI

#include "OGComparison.h"
#include "OGComparisonPrivate.h"

const void *OGComparisonStateGetDestination(OGComparisonState state) {
    return state->destination;
}

const void *OGComparisonStateGetSource(OGComparisonState state) {
    return state->source;
}

OGFieldRange OGComparisonStateGetFieldRange(OGComparisonState state) {
    return state->field_range;
}

OGTypeID OGComparisonStateGetFieldType(OGComparisonState state) {
    return state->field_type;
}

bool OGCompareValues(const void *lhs, const void *rhs, OGTypeID type, OGComparisonOptions options) {
    // TODO
    return false;
}

const unsigned char *_Nullable OGPrefetchCompareValues(OGTypeID type_id,
                                                       OGComparisonOptions options,
                                                       uint32_t priority) {
    // TODO
    return nullptr;
}

void OGOverrideComparisonForTypeDescriptor(void *descriptor, OGComparisonMode mode) {
    // TODO
}
