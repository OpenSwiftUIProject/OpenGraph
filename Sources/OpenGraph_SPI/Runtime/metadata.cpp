//
//  metadata.cpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#include "metadata.hpp"

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED

using OG::swift::metadata;

void const* metadata::descriptor() const OG_NOEXCEPT {
    // TODO
    return nullptr;
}

void const* metadata::nominal_descriptor() const OG_NOEXCEPT {
    void const* descriptor = this->descriptor();
    if (descriptor == nullptr) {
        return nullptr;
    }
    // TODO
    return nullptr;
}


void metadata::append_description(CFMutableStringRef description) const OG_NOEXCEPT {
    // TODO
}

#endif /* OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED */
