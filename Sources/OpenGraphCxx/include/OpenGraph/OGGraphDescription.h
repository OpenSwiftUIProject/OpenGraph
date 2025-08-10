//
//  OGGraphDescription.h
//  OpenGraphCxx

#ifndef OGGraphDescription_h
#define OGGraphDescription_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

#if OG_OBJC_FOUNDATION

typedef CFStringRef OGDescriptionOption OG_SWIFT_STRUCT OG_SWIFT_NAME(DescriptionOption);

OG_EXPORT
const OGDescriptionOption OGDescriptionFormat OG_SWIFT_NAME(DescriptionOption.format);

OG_EXPORT
const OGDescriptionOption OGDescriptionIncludeValues OG_SWIFT_NAME(DescriptionOption.includeValues);

OG_EXPORT
const OGDescriptionOption OGDescriptionTruncationLimit OG_SWIFT_NAME(DescriptionOption.truncationLimit);

OG_EXPORT
const OGDescriptionOption OGDescriptionMaxFrames OG_SWIFT_NAME(DescriptionOption.maxFrames);

static const CFStringRef OGDescriptionFormatDot OG_SWIFT_NAME(OGGraphRef.descriptionFormatDot) = CFSTR("graph/dot");

static const CFStringRef OGDescriptionFormatDictionary OG_SWIFT_NAME(OGGraphRef.descriptionFormatDictionary) = CFSTR("graph/dict");

static const CFStringRef OGDescriptionAllGraphs OG_SWIFT_NAME(OGGraphRef.descriptionAllGraphs) = CFSTR("all_graphs");

#endif

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON(char const * _Nullable name) OG_SWIFT_NAME(OGGraphRef.archiveJSON(name:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON2(char const * _Nullable name, bool exclude_values) OG_SWIFT_NAME(OGGraphRef.archiveJSON(name:excludeValues:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
_Nullable CFTypeRef OGGraphDescription(_Nullable OGGraphRef graph, CFDictionaryRef options) OG_SWIFT_NAME(OGGraphRef.description(_:options:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphDescription_h */
