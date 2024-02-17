//
//  AGUniqueID.h
//  
//
//  Created by Kyle on 2023/10/9.
//

#ifndef AGUniqueID_h
#define AGUniqueID_h

#include "AGBase.h"
typedef long long AGUniqueID;

AG_EXTERN_C_BEGIN
AG_EXPORT
AG_REFINED_FOR_SWIFT
AGUniqueID AGMakeUniqueID(void) AG_SWIFT_NAME(makeUniqueID());
AG_EXTERN_C_END

#endif /* AGUniqueID_h */
