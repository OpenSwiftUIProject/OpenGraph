//
//  metadata.hpp
//  OpenGraphCxx
//
//  Audited for iOS 18.0
//  Status: WIP

#ifndef metadata_hpp
#define metadata_hpp

#include <OpenGraph/OGBase.h>

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
#include <swift/Runtime/Metadata.h>
#include <swift/Runtime/HeapObject.h>
using namespace swift;
#endif /* OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED */

namespace OG {
namespace swift {
#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
class metadata: public Metadata {
public:
    OG_INLINE OG_CONSTEXPR
    Metadata const* getType() const OG_NOEXCEPT {
        return this;
    }
    
    OG_INLINE OG_CONSTEXPR
    TypeNamePair const name(bool qualified) const OG_NOEXCEPT {
        return swift_getTypeName(getType(), qualified);
    }
    
    OG_INLINE OG_CONSTEXPR
    MetadataKind const getKind() const OG_NOEXCEPT {
        return getType()->getKind();
    }
    
    OG_INLINE OG_CONSTEXPR
    TypeContextDescriptor const* descriptor() const OG_NOEXCEPT {
        switch (getKind()) {
            case MetadataKind::Class: {
                const auto cls = static_cast<const ClassMetadata *>(getType());
                // We may build this with a newer OS SDK but run on old OS.
                // So instead of using `isTypeMetadata` / `(Data & SWIFT_CLASS_IS_SWIFT_MASK)`,
                // we manully use 3 here to check isTypeMetadata
                if ((cls->Data & 3) == 0) return nullptr;
                return cls->getDescription();
            }
            case MetadataKind::Struct:
            case MetadataKind::Enum:
            case MetadataKind::Optional: {                
                return static_cast<const TargetValueMetadata<InProcess> *>(getType())->Description;
            }
            default:
                return nullptr;
        }
    }
    
    OG_INLINE OG_CONSTEXPR
    TypeContextDescriptor const* nominal_descriptor() const OG_NOEXCEPT {
        auto descriptor = this->descriptor();
        if (descriptor == nullptr) {
            return nullptr;
        }
        switch(descriptor->getKind()) {
            case ContextDescriptorKind::Struct:
            case ContextDescriptorKind::Enum:
                return descriptor;
            default:
                return nullptr;
        }
    }
    
    void append_description(CFMutableStringRef description) const OG_NOEXCEPT;
}; /* OG::swift::metadata */
#else
class metadata {};
#endif /* OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED */
} /* OG::swift */
} /* OG */

#endif /* metadata_hpp */
