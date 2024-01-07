//
//  AGAttribute.hpp
//
//
//  Created by Kyle on 2023/8/30.
//


#ifndef AGAttribute_hpp
#define AGAttribute_hpp

#include <stdlib.h>
#include <CoreFoundation/CoreFoundation.h>

typedef uint32_t AGAttribute __attribute((swift_newtype(struct)));

CF_EXPORT
const AGAttribute AGAttributeNil;

#endif /* AGAttribute_hpp */
