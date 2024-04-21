#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif

#include "AGAttribute.h"
#include "AGAttributeFlags.h"
#include "AGAttributeInfo.h"
#include "AGAttributeType.h"
#include "AGAttributeTypeFlags.h"
#include "AGBase.h"
#include "AGCachedValueOptions.h"
#include "AGChangedValueFlags.h"
#include "AGCompareValues.h"
#include "AGComparisonMode.h"
#include "AGCounterQueryType.h"
#include "AGDebugServer.h"
#include "AGGraph.h"
#include "AGGraphContext.h"
#include "AGGraphDescription.h"
#include "AGInputOptions.h"
#include "AGSearchOptions.h"
#include "AGSubgraph.h"
#include "AGSwiftMetadata.h"
#include "AGTupleType.h"
#include "AGTypeApplyEnumData.h"
#include "AGTypeApplyField.h"
#include "AGTypeApplyOptions.h"
#include "AGTypeDescription.h"
#include "AGTypeID.h"
#include "AGTypeKind.h"
#include "AGUniqueID.h"
#include "AGValue.h"
#include "AGValueOptions.h"
#include "AGValueState.h"
#include "AGWeakAttribute.h"

FOUNDATION_EXPORT double AGAttributeVersionNumber;
FOUNDATION_EXPORT const unsigned char AGAttributeVersionString[];
