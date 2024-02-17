//
//  OGAttribute.cpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#include "OGAttribute.h"
#include "AttributeID.hpp"
#include "../Attribute/AttributeID.hpp"
#include "../Util/assert.hpp"
#include <optional>

const OGAttribute OGAttributeNil = OGAttribute(OG::AttributeID::Kind::Nil);

OGAttribute OGGraphGetCurrentAttribute() {
    // TODO
    return OGAttributeNil;
}

namespace {
OGAttribute create_offset_attribute(OGAttribute attribute, uint64_t offset, std::optional<uint64_t> size) {
    // TODO
    return OGAttributeNil;
}
}

OGAttribute OGGraphCreateOffsetAttribute(OGAttribute attribute, uint64_t offset) {
    return create_offset_attribute(attribute, offset, std::nullopt);
}

OGAttribute OGGraphCreateOffsetAttribute2(OGAttribute attribute, uint64_t offset, uint64_t size) {
    return create_offset_attribute(attribute, offset, std::optional(size));
}

OGAttributeFlags OGGraphGetFlags(OGAttribute attribute) {
    const OG::AttributeID id = OG::AttributeID(attribute);
    if (!id.isDirect()) {
        OG::precondition_failure("non-direct attribute id: %u", id);
    }
    // TODO: data/table
    return OGAttributeFlags_0;
}

void OGGraphSetFlags(OGAttribute attribute, OGAttributeFlags flags) {
    const OG::AttributeID id = OG::AttributeID(attribute);
    if (!id.isDirect()) {
        OG::precondition_failure("non-direct attribute id: %u", id);
    }
    // TODO: data/table
}
