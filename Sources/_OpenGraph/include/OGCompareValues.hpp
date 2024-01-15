//
//  OGCompareValues.hpp
//  
//
//  Created by Kyle on 2023/10/9.
//

#ifndef OGCompareValues_hpp
#define OGCompareValues_hpp

#include "OGBase.hpp"
#include "OGComparisonMode.hpp"
#include <stdbool.h>

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGCompareValues(const void *lhs, const void *rhs, const void *type, const OGComparisonMode comparisonMode);
OG_EXTERN_C_END

#endif /* OGCompareValues_hpp */
