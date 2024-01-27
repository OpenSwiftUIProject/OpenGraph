//
//  AGAttribute.hpp
//
//
//  Created by Kyle on 2023/8/30.
//


#ifndef AGAttribute_hpp
#define AGAttribute_hpp

#include "AGBase.hpp"

typedef uint32_t AGAttribute __attribute((swift_newtype(struct)));

AG_EXPORT
const AGAttribute AGAttributeNil;

#endif /* AGAttribute_hpp */
