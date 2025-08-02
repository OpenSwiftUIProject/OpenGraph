//
//  OGMakeUniqueID.h
//  OpenGraphCxx
//
//  Audited for iOS 18.0
//  Status: Complete

#ifndef OGMakeUniqueID_h
#define OGMakeUniqueID_h

#include "OGBase.h"
typedef long OGUniqueID;

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGMakeUniqueID(void) OG_SWIFT_NAME(makeUniqueID());
OG_EXTERN_C_END

#endif /* OGMakeUniqueID_h */
