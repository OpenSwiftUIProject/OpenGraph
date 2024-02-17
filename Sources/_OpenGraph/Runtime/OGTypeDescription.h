//
//  OGTypeDescription.h
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef OGTypeDescription_h
#define OGTypeDescription_h

#include "OGBase.h"
#include "OGTypeID.h"

#if TARGET_OS_DARWIN
OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
CFStringRef OGTypeDescription(OGTypeID type);
OG_EXTERN_C_END
#endif /* TARGET_OS_DARWIN */

#endif /* OGTypeDescription_h */
