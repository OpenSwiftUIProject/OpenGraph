//
//  OGBase.hpp
//
//
//  Created by Kyle on 2024/1/16.
//

#ifndef OGBase_h
#define OGBase_h

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#define OG_OPTIONS CF_OPTIONS
#define OG_EXTERN_C_BEGIN CF_EXTERN_C_BEGIN
#define OG_EXTERN_C_END CF_EXTERN_C_END
#define OG_EXPORT CF_EXPORT
#define OG_REFINED_FOR_SWIFT CF_REFINED_FOR_SWIFT
#define OG_SWIFT_NAME CF_SWIFT_NAME
#else
#include <OpenFoundation/OpenFoundation.h>
#define OG_OPTIONS OF_OPTIONS
#define OG_EXTERN_C_BEGIN OF_EXTERN_C_BEGIN
#define OG_EXTERN_C_END OF_EXTERN_C_END
#define OG_EXPORT OF_EXPORT
#define OG_REFINED_FOR_SWIFT OF_REFINED_FOR_SWIFT
#define OG_SWIFT_NAME OF_SWIFT_NAME
#endif /* __APPLE__ */
#endif /* OGBase_h */
