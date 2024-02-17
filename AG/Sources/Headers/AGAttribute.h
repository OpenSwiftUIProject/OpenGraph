//
//  AGAttribute.h
//
//
//  Created by Kyle on 2023/8/30.
//


#ifndef AGAttribute_h
#define AGAttribute_h

#include "AGBase.h"

typedef uint32_t AGAttribute __attribute((swift_newtype(struct)));

AG_EXPORT
const AGAttribute AGAttributeNil;

#endif /* AGAttribute_h */
