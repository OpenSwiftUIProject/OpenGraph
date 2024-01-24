//
//  OGTypeApplyField.hpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#ifndef OGTypeApplyField_hpp
#define OGTypeApplyField_hpp

#include "OGBase.hpp"
#include "OGTypeApplyOptions.hpp"

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTypeApplyFields(const void *type, const void *block, void *context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGTypeApplyFields2(const void *type, OGTypeApplyOptions options, const void *block, void *context);

OG_EXTERN_C_END

#endif /* OGTypeApplyField_hpp */
