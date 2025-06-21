//
//  OGCompareValues.h
//  OpenGraph_SPI

#ifndef OGCompareValues_h
#define OGCompareValues_h

#include "OGBase.h"
#include "OGComparisonMode.h"

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGCompareValues(const void *lhs, const void *rhs, const void *type, const OGComparisonMode comparisonMode);
OG_EXTERN_C_END

#endif /* OGCompareValues_h */
