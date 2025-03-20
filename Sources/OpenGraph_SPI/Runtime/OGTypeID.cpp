//
//  OGTypeID.cpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: WIP

#include "OGTypeID.h"
#include "metadata.hpp"
#include "../Util/assert.hpp"

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
#include <swift/Runtime/Metadata.h>
#endif

OGTypeKind OGTypeGetKind(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    switch (metadata->getKind()) {
        case swift::MetadataKind::Class: // 0x0
            return OGTypeKindClass;
        case swift::MetadataKind::Struct: // 0x200
            return OGTypeKindStruct;
        case swift::MetadataKind::Enum: // 0x201
            return OGTypeKindEnum;
        case swift::MetadataKind::Optional: // 0x202
            return OGTypeKindOptional;
        case swift::MetadataKind::Tuple: // 0x301
            return OGTypeKindTuple;
        case swift::MetadataKind::Function: // 0x302
            return OGTypeKindFunction;
        case swift::MetadataKind::Existential: // 0x303
            return OGTypeKindExistential;
        case swift::MetadataKind::Metatype: // 0x304
            return OGTypeKindMetatype;
        default:
            return OGTypeKindNone;
    }
    #else
    return OGTypeKindNone;
    #endif
}

void OGTypeApplyFields(const void *type, const void *block, void *context) {
    // TODO
    return;
}

bool OGTypeApplyFields2(const void *type, OGTypeApplyOptions options, const void *block, void *context) {
    // TODO
    return false;
}

#if OPENGRAPH_RELEASE >= OPENGRAPH_RELEASE_2024

uint32_t OGTypeGetEnumTag(OGTypeID typeID, const void *value) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    auto vwt = metadata->getValueWitnesses();
    if (!swift::EnumValueWitnessTable::classof(vwt)) {
        OG::precondition_failure("not an enum type: %s", metadata->name(false).data);
    }
    auto enum_vwt = static_cast<const swift::EnumValueWitnessTable *>(vwt);
    return enum_vwt->getEnumTag(static_cast<const swift::OpaqueValue *>(value), metadata);
    #else
    return 0;
    #endif
}

void OGTypeProjectEnumData(OGTypeID typeID, void *value) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    auto vwt = metadata->getValueWitnesses();
    if (!swift::EnumValueWitnessTable::classof(vwt)) {
        OG::precondition_failure("not an enum type: %s", metadata->name(false).data);
    }
    auto enum_vwt = static_cast<const swift::EnumValueWitnessTable *>(vwt);
    enum_vwt->destructiveProjectEnumData(static_cast<swift::OpaqueValue *>(value), metadata);
    #else
    return;
    #endif
}

void OGTypeInjectEnumTag(OGTypeID typeID, uint32_t tag, void *value) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    auto vwt = metadata->getValueWitnesses();
    if (!swift::EnumValueWitnessTable::classof(vwt)) {
        OG::precondition_failure("not an enum type: %s", metadata->name(false).data);
    }
    auto enum_vwt = static_cast<const swift::EnumValueWitnessTable *>(vwt);
    return enum_vwt->destructiveInjectEnumTag(static_cast<swift::OpaqueValue *>(value), tag, metadata);
    #else
    return;
    #endif
}

#endif /* OPENGRAPH_RELEASE */

bool OGTypeApplyEnumData() {
    // TODO
    return false;
}

bool OGTypeApplyMutableEnumData() {
    // TODO
    return false;
}

CFStringRef OGTypeDescription(OGTypeID typeID) {
    CFMutableStringRef ref = CFStringCreateMutable(CFAllocatorGetDefault(), 0);
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    metadata->append_description(ref);
    #endif
    return ref;
}

#if OPENGRAPH_RELEASE >= OPENGRAPH_RELEASE_2024

OGTypeSignature const OGTypeGetSignature(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    // TODO
    return OGTypeSignature{};
    #else
    return OGTypeSignature{};
    #endif
}
void const* OGTypeGetDescriptor(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    return metadata->descriptor();
    #else
    return nullptr;
    #endif
}

#endif /* OPENGRAPH_RELEASE */

void const* OGTypeNominalDescriptor(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    return metadata->nominal_descriptor();
    #else
    return nullptr;
    #endif
}

char const* OGTypeNominalDescriptorName(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(typeID);
    auto nominal_descriptor = metadata->nominal_descriptor();
    if (nominal_descriptor == nullptr) {
        return nullptr;
    }
    return nominal_descriptor->Name.get();
    #else
    return nullptr;
    #endif
}
