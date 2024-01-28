//
//  AGCompareValues.hpp
//
//
//  Created by Kyle on 2023/10/9.
//

#ifndef AGCompareValues_hpp
#define AGCompareValues_hpp

#include "AGBase.hpp"
#include "AGComparisonMode.hpp"
#include <stdbool.h>

AG_EXTERN_C_BEGIN
AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGCompareValues(const void *lhs, const void *rhs, const AGComparisonMode comparisonMode, const void *type);
AG_EXTERN_C_END

#endif /* AGCompareValues_hpp */
