//
//  AGTypeDescription.hpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef AGTypeDescription_hpp
#define AGTypeDescription_hpp

#include "AGBase.hpp"
#include "AGTypeID.hpp"

AG_EXTERN_C_BEGIN
AG_EXPORT
AG_REFINED_FOR_SWIFT
CFStringRef AGTypeDescription(AGTypeID type);
AG_EXTERN_C_END

#endif /* AGTypeDescription_hpp */
