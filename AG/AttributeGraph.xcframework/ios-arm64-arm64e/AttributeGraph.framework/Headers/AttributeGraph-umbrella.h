#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif

#include "AGAttribute.hpp"
#include "AGBase.hpp"
#include "AGCompareValues.hpp"
#include "AGComparisonMode.hpp"
#include "AGGraph.hpp"
#include "AGSubgraph.hpp"
#include "AGSwiftMetadata.hpp"
#include "AGTupleType.hpp"
#include "AGTypeApplyEnumData.hpp"
#include "AGTypeApplyField.hpp"
#include "AGTypeApplyOptions.hpp"
#include "AGTypeDescription.hpp"
#include "AGTypeID.hpp"
#include "AGTypeKind.hpp"
#include "AGUniqueID.hpp"

FOUNDATION_EXPORT double AGAttributeVersionNumber;
FOUNDATION_EXPORT const unsigned char AGAttributeVersionString[];

