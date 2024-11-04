//
//  OGMakeUniqueID.h
//  
//
//  Created by Kyle on 2023/10/9.
//

#ifndef OGMakeUniqueID_h
#define OGMakeUniqueID_h

#include "OGBase.h"
typedef long long OGUniqueID;

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGMakeUniqueID(void) OG_SWIFT_NAME(makeUniqueID());
OG_EXTERN_C_END

#endif /* OGMakeUniqueID_h */
