#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif

#import "AGAttribute.hpp"
#import "AGUniqueID.hpp"
#import "AGComparisonMode.hpp"
#import "AGCompareValues.hpp"

FOUNDATION_EXPORT double AGAttributeVersionNumber;
FOUNDATION_EXPORT const unsigned char AGAttributeVersionString[];

