//
//  AGTypeApplyField.hpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef AGTypeApplyField_hpp
#define AGTypeApplyField_hpp

#include "AGBase.hpp"
#include "AGTypeApplyOptions.hpp"

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGTypeApplyFields(const void *type, const void *block, void *context);

AG_EXPORT
AG_REFINED_FOR_SWIFT
bool AGTypeApplyFields2(const void *type, AGTypeApplyOptions options, const void *block, void *context);

AG_EXTERN_C_END

#endif /* AGTypeApplyField_hpp */
