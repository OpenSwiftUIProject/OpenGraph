//
//  AGTypeDescription.h
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef AGTypeDescription_h
#define AGTypeDescription_h

#include "AGBase.h"
#include "AGTypeID.h"

AG_ASSUME_NONNULL_BEGIN

#if TARGET_OS_DARWIN
AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
CFStringRef AGTypeDescription(AGTypeID type);

AG_EXTERN_C_END

#endif /* TARGET_OS_DARWIN */

AG_ASSUME_NONNULL_END

#endif /* AGTypeDescription_h */
