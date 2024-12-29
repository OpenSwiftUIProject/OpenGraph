#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif

#include "OGAttribute.h"
#include "OGAttributeFlags.h"
#include "OGAttributeInfo.h"
#include "OGAttributeType.h"
#include "OGAttributeTypeFlags.h"
#include "OGBase.h"
#include "OGCachedValueOptions.h"
#include "OGChangedValueFlags.h"
#include "OGCompareValues.h"
#include "OGComparisonMode.h"
#include "OGCounterQueryType.h"
#include "OGDebugServer.h"
#include "OGGraph.h"
#include "OGGraphContext.h"
#include "OGInputOptions.h"
#include "OGSearchOptions.h"
#include "OGSubgraph.h"
#include "OGTupleType.h"
#include "OGTypeApplyEnumData.h"
#include "OGTypeApplyField.h"
#include "OGTypeApplyOptions.h"
#include "OGTypeID.h"
#include "OGUniqueID.h"
#include "OGValue.h"
#include "OGValueOptions.h"
#include "OGValueState.h"
#include "OGWeakAttribute.h"

FOUNDATION_EXPORT double AGAttributeVersionNumber;
FOUNDATION_EXPORT const unsigned char AGAttributeVersionString[];
