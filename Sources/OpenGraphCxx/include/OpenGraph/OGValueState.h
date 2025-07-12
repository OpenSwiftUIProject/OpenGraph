//
//  OGValueState.h
//  OpenGraphCxx

#ifndef OGValueState_h
#define OGValueState_h

#include <OpenGraph/OGBase.h>

OG_ASSUME_NONNULL_BEGIN

typedef OG_OPTIONS(uint8_t, OGValueState) {
    OGValueStateNone = 0,
    OGValueStateDirty = 1 << 0,
    OGValueStatePending = 1 << 1,
    OGValueStateUpdating = 1 << 2,
    OGValueStateValueExists = 1 << 3,
    OGValueStateMainThread = 1 << 4,
    OGValueStateMainRef = 1 << 5,
    OGValueStateRequiresMainThread = 1 << 6,
    OGValueStateSelfModified = 1 << 7,
};

OG_ASSUME_NONNULL_END

#endif /* OGValueState_h */
