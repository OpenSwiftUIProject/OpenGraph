//
//  OGVersion.h
//  OpenGraph

#ifndef OGVersion_h
#define OGVersion_h

#include "OGBase.h"

#define OPENGRAPH_RELEASE_2021 2021
#define OPENGRAPH_RELEASE_2024 2024

#ifndef OPENGRAPH_RELEASE
#define OPENGRAPH_RELEASE OPENGRAPH_RELEASE_2024
#endif

OG_EXTERN_C_BEGIN

OG_EXPORT const uint64_t OGVersion;

OG_EXTERN_C_END

#endif /* OGVersion_h */
