//
//  AGCompareValues.h
//
//
//  Created by Kyle on 2023/10/9.
//

#ifndef AGCompareValues_h
#define AGCompareValues_h

#include "AGBase.h"
#include "AGComparisonMode.h"

AG_EXTERN_C_BEGIN
AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGCompareValues(const void *lhs, const void *rhs, const void *type, const AGComparisonMode comparisonMode);
AG_EXTERN_C_END

#endif /* AGCompareValues_h */
