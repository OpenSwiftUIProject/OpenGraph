//
//  metadata.hpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#ifndef metadata_hpp
#define metadata_hpp

#include "OGBase.h"

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
#include <swift/Runtime/Metadata.h>
#endif

namespace OG {
namespace swift {
#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
class metadata: public ::swift::Metadata {
public:
    void const* descriptor() const OG_NOEXCEPT;
    void const* nominal_descriptor() const OG_NOEXCEPT;
    
    void append_description(CFMutableStringRef description) const OG_NOEXCEPT;
}; /* OG::swift::metadata */
#else
class metadata {};
#endif /* OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED */
} /* OG::swift */
} /* OG */

#endif /* metadata_hpp */
