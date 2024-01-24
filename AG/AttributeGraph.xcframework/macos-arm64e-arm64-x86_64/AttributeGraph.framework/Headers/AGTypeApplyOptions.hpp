//
//  AGTypeApplyOptions.hpp
//  
//
//  Created by Kyle on 2024/1/10.
//

#ifndef AGTypeApplyOptions_hpp
#define AGTypeApplyOptions_hpp

#include <CoreFoundation/CoreFoundation.h>

typedef CF_OPTIONS(uint32_t, AGTypeApplyOptions) {
    AGTypeApplyOptions_0 = 0,
    AGTypeApplyOptions_1 = 1 << 0,
    AGTypeApplyOptions_2 = 1 << 1,
    AGTypeApplyOptions_4 = 1 << 2,
};

#endif /* AGTypeApplyOptions_hpp */
