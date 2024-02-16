//
//  OGMakeUniqueID.hpp
//  
//
//  Created by Kyle on 2023/10/9.
//

#ifndef OGMakeUniqueID_hpp
#define OGMakeUniqueID_hpp

#include "OGBase.hpp"
typedef long long OGUniqueID;

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGMakeUniqueID(void) OG_SWIFT_NAME(makeUniqueID());
OG_EXTERN_C_END

#endif /* OGMakeUniqueID_hpp */
