//
//  OGUniqueID.h
//  OpenGraphCxx
//
//  Audited for iOS 18.0
//  Status: Complete

#ifndef OGUniqueID_h
#define OGUniqueID_h

#include <OpenGraph/OGBase.h>
typedef long OGUniqueID;

OG_EXTERN_C_BEGIN
OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGMakeUniqueID(void) OG_SWIFT_NAME(makeUniqueID());
OG_EXTERN_C_END

#endif /* OGUniqueID_h */
