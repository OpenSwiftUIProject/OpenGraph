//
//  AttributeID.hpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef AttributeID_hpp
#define AttributeID_hpp

#include "OGBase.hpp"
#include "OGAttribute.hpp"

namespace OG {
class AttributeID final {
private:
    uint32_t _rawValue;
public:
    OG_INLINE OG_CONSTEXPR
    AttributeID(OGAttribute attribute) OG_NOEXCEPT:
    _rawValue(attribute) {}
};
}

#endif /* AttributeID_hpp */
