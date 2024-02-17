//
//  AGComparisonMode.h
//
//
//  Created by Kyle on 2023/12/20.
//

#ifndef AGComparisonMode_h
#define AGComparisonMode_h

#include "AGBase.h"

typedef AG_OPTIONS(uint32_t, AGComparisonMode) {
    AGComparisonMode_0 = 0,
    AGComparisonMode_1 = 1 << 0,
    AGComparisonMode_2 = 1 << 1,
    AGComparisonMode_3 = AGComparisonMode_1 | AGComparisonMode_2,
};

typedef AG_OPTIONS(uint32_t, AGComparisonOptions) {
    AGComparisonOptions_0 = 0,
    AGComparisonOptions_1 = 1 << 0,
    AGComparisonOptions_2 = 1 << 1,
    AGComparisonOptions_3 = AGComparisonOptions_1 | AGComparisonOptions_2,
};

#endif /* AGComparisonMode_h */

