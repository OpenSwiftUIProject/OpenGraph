//
//  OGAttribute.hpp
//  
//
//  Created by Kyle on 2023/9/25.
//

#ifndef OGAttribute_hpp
#define OGAttribute_hpp

#include "OGBase.hpp"

typedef uint32_t OGAttribute __attribute((swift_newtype(struct)));

OG_EXTERN_C_BEGIN
OG_EXPORT
const OGAttribute OGAttributeNil;
OG_EXTERN_C_END

#endif /* OGAttribute_hpp */

