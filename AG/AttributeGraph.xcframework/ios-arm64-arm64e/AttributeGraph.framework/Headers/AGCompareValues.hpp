//
//  AGCompareValues.hpp
//
//
//  Created by Kyle on 2023/10/9.
//

#ifndef AGCompareValues_hpp
#define AGCompareValues_hpp

#include <CoreFoundation/CoreFoundation.h>
#include "AGComparisonMode.hpp"
#include <stdbool.h>

CF_EXTERN_C_BEGIN
CF_EXPORT
CF_REFINED_FOR_SWIFT
bool AGCompareValues(const void *lhs, const void *rhs, const AGComparisonMode comparisonMode, const void *type);
CF_EXTERN_C_END

#endif /* AGCompareValues_hpp */
