//
//  OGGraphDescription.h
//  OpenGraphCxx

#ifndef OGGraphDescription_h
#define OGGraphDescription_h

#include <OpenGraphC/OGBase.h>
#include <OpenGraphC/OGGraph.h>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

#if OG_OBJC_FOUNDATION

OG_EXPORT
const CFStringRef OGDescriptionFormat OG_SWIFT_NAME(OGGraphRef.descriptionFormat);

OG_EXPORT
const CFStringRef OGDescriptionIncludeValues OG_SWIFT_NAME(OGGraphRef.descriptionIncludeValues);

static const CFStringRef OGDescriptionFormatDot OG_SWIFT_NAME(OGGraphRef.descriptionFormatDot) = CFSTR("graph/dot");

static const CFStringRef OGDescriptionFormatDictionary OG_SWIFT_NAME(OGGraphRef.descriptionFormatDictionary) = CFSTR("graph/dict");

static const CFStringRef OGDescriptionAllGraphs OG_SWIFT_NAME(OGGraphRef.descriptionAllGraphs) = CFSTR("all_graphs");

#endif

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON(char const * _Nullable name) OG_SWIFT_NAME(OGGraphRef.archiveJSON(name:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON2(char const * _Nullable name, uint8_t options) OG_SWIFT_NAME(OGGraphRef.archiveJSON(name:options:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
_Nullable CFTypeRef OGGraphDescription(_Nullable OGGraphRef graph, CFDictionaryRef options) OG_SWIFT_NAME(OGGraphRef.description(_:options:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphDescription_h */
