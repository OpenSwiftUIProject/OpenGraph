//
//  OGGraphDescription.h
//  OpenGraph_SPI

#ifndef OGGraphDescription_h
#define OGGraphDescription_h

#include "OGBase.h"

OG_ASSUME_NONNULL_BEGIN

#if OG_OBJC_FOUNDATION
OG_EXTERN_C_BEGIN

OG_EXPORT
const CFStringRef OGDescriptionFormat OG_SWIFT_NAME(OGGraphRef.descriptionFormat);

OG_EXPORT
const CFStringRef OGDescriptionMaxFrames OG_SWIFT_NAME(OGGraphRef.maxFrames);

OG_EXPORT
const CFStringRef OGDescriptionIncludeValues OG_SWIFT_NAME(OGGraphRef.includeValues);

OG_EXPORT
const CFStringRef OGDescriptionTruncationLimit OG_SWIFT_NAME(OGGraphRef.truncationLimit);

OG_EXTERN_C_END
#endif

OG_ASSUME_NONNULL_END

#endif /* OGGraphDescription_h */
