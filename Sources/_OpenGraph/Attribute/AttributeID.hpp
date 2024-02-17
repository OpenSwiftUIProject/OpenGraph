//
//  AttributeID.hpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef AttributeID_hpp
#define AttributeID_hpp

#include "OGBase.h"
#include "OGAttribute.h"

namespace OG {
class AttributeID final {
public:
    enum : uint32_t {
      KindMask =            0x00000003, // Bits 0-1
      // unused/unknown     0x0000FF00,
    };
    enum class Kind: uint8_t {
        Direct = 0x0,
        Indirect = 0x1,
        Nil = 0x2,
    };
private:
    uint32_t _rawValue;
    
    OG_INLINE OG_CONSTEXPR
    const Kind getKind() const OG_NOEXCEPT {
        return Kind(_rawValue & KindMask);
    }
public:
    OG_INLINE OG_CONSTEXPR
    AttributeID(OGAttribute attribute) OG_NOEXCEPT:
    _rawValue(attribute) {}
    
    OG_INLINE OG_CONSTEXPR
    AttributeID(const AttributeID &) noexcept = default;
    
    OG_INLINE OG_CONSTEXPR
    AttributeID(AttributeID &&) noexcept = default;
    
    OG_INLINE OG_CONSTEXPR
    AttributeID &operator=(const AttributeID &) noexcept = default;
    
    OG_INLINE OG_CONSTEXPR
    AttributeID &operator=(AttributeID &&) noexcept = default;
    
    OG_INLINE OG_CONSTEXPR
    const bool isDirect() const OG_NOEXCEPT {
        return getKind() == Kind::Direct;
    }
    
    OG_INLINE OG_CONSTEXPR
    const bool isIndirect() const OG_NOEXCEPT {
        return getKind() == Kind::Direct;
    }
    
    OG_INLINE OG_CONSTEXPR
    const bool isNil() const OG_NOEXCEPT {
        return getKind() == Kind::Nil;
    }
};
static_assert(sizeof(AttributeID) == sizeof(uint32_t));
}

#endif /* AttributeID_hpp */
