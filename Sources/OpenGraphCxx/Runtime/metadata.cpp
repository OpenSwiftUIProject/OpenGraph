//
//  metadata.cpp
//  OpenGraphCxx
//
//  Audited for iOS 18.0
//  Status: WIP

#include <OpenGraphCxx/Runtime/metadata.hpp>

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED

using OG::swift::metadata;

void metadata::append_description(CFMutableStringRef description) const OG_NOEXCEPT {
    // TODO
}

#endif /* OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED */
