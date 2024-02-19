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
#include "AGCompareValues.h"
#include "AGComparisonMode.h"
#include "AGDebugServer.h"
#include "AGGraph.h"
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

FOUNDATION_EXPORT double AGAttributeVersionNumber;
FOUNDATION_EXPORT const unsigned char AGAttributeVersionString[];

