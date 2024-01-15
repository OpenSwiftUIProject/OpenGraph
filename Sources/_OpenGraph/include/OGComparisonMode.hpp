//
//  OGComparisonMode.hpp
//
//
//  Created by Kyle on 2023/12/20.
//

#ifndef OGComparisonMode_hpp
#define OGComparisonMode_hpp

#include "OGBase.hpp"

typedef OG_OPTIONS(uint32_t, OGComparisonMode) {
    OGComparisonMode_0 = 0,
    OGComparisonMode_1 = 1 << 0,
    OGComparisonMode_2 = 1 << 1,
    OGComparisonMode_3 = OGComparisonMode_1 | OGComparisonMode_2,
};

typedef OG_OPTIONS(uint32_t, OGComparisonOptions) {
    OGComparisonOptions_0 = 0,
    OGComparisonOptions_1 = 1 << 0,
    OGComparisonOptions_2 = 1 << 1,
    OGComparisonOptions_3 = OGComparisonOptions_1 | OGComparisonOptions_2,
};

#endif /* OGComparisonMode_hpp */

