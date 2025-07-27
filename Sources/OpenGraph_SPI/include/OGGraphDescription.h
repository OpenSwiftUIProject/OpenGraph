//
//  OGGraphDescription.h
//  OpenGraph_SPI

#ifndef OGGraphDescription_h
#define OGGraphDescription_h

#include "OGBase.h"

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

#if OG_OBJC_FOUNDATION

OG_EXPORT
const CFStringRef OGDescriptionFormat OG_SWIFT_NAME(OGGraphRef.descriptionFormat);

OG_EXPORT
const CFStringRef OGDescriptionIncludeValues OG_SWIFT_NAME(OGGraphRef.descriptionIncludeValues);

static const CFStringRef OGDescriptionFormatDot OG_SWIFT_NAME(OGGraphRef.descriptionFormatDot) = CFSTR("graph/dot");

static const CFStringRef OGDescriptionFormatDictionary OG_SWIFT_NAME(OGGraphRef.descriptionFormatDictionary) = CFSTR("graph/dictionary");

static const CFStringRef OGDescriptionAllGraphs OG_SWIFT_NAME(OGGraphRef.descriptionAllGraphs) = CFSTR("all_graphs");

#endif

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphDescription_h */
