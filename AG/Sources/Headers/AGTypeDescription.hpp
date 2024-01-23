//
//  AGTypeDescription.hpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef AGTypeDescription_hpp
#define AGTypeDescription_hpp

#include <CoreFoundation/CoreFoundation.h>
#include "AGTypeID.hpp"

CF_EXTERN_C_BEGIN
CF_EXPORT
CF_REFINED_FOR_SWIFT
CFStringRef AGTypeDescription(AGTypeID type);
CF_EXTERN_C_END

#endif /* AGTypeDescription_hpp */
