//
//  OGTypeApplyField.hpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef OGTypeApplyField_hpp
#define OGTypeApplyField_hpp

#include <CoreFoundation/CoreFoundation.h>
#include "AGTypeApplyOptions.hpp"

CF_EXTERN_C_BEGIN

CF_EXPORT
CF_REFINED_FOR_SWIFT
void OGTypeApplyFields(const void *type, const void *block, void *context);

CF_EXPORT
CF_REFINED_FOR_SWIFT
bool OGTypeApplyFields2(const void *type, AGTypeApplyOptions options, const void *block, void *context);

CF_EXTERN_C_END

#endif /* OGTypeApplyField_hpp */
