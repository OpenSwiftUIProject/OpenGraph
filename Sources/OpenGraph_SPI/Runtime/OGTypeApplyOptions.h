//
//  OGTypeApplyOptions.h
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef OGTypeApplyOptions_h
#define OGTypeApplyOptions_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGTypeApplyOptions) {
    OGTypeApplyOptions_0 = 0,
    OGTypeApplyOptions_1 = 1 << 0,
    OGTypeApplyOptions_2 = 1 << 1,
    OGTypeApplyOptions_4 = 1 << 2,
};

#endif /* OGTypeApplyOptions_h */
