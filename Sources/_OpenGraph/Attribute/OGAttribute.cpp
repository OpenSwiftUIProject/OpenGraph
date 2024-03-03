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

OGAttribute OGGraphCreateOffsetAttribute(OGAttribute attribute, long offset) {
    return create_offset_attribute(attribute, offset, std::nullopt);
}

OGAttribute OGGraphCreateOffsetAttribute2(OGAttribute attribute, long offset, uint64_t size) {
    return create_offset_attribute(attribute, offset, std::optional(size));
}

namespace {
OGAttribute create_indirect_attribute(OGAttribute attribute, std::optional<uint64_t> size) {
    // TODO
    return OGAttributeNil;
}
}

OGAttribute OGGraphCreateIndirectAttribute(OGAttribute attribute) {
    return create_indirect_attribute(attribute, std::nullopt);
}

OGAttribute OGGraphCreateIndirectAttribute2(OGAttribute attribute, uint64_t size) {
    return create_indirect_attribute(attribute, std::optional(size));
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

void OGGraphAddInput(OGAttribute attribute1, OGAttribute attribute2, OGInputOptions options, long token) {
    const OG::AttributeID id = OG::AttributeID(attribute1);
    if (!id.isDirect()) {
        OG::precondition_failure("non-direct attribute id: %u", id);
    }
    // TODO: data/table
}

const OGAttributeInfo OGGraphGetAttributeInfo(OGAttribute attribute) {
    const OG::AttributeID id = OG::AttributeID(attribute);
    if (!id.isDirect()) {
        OG::precondition_failure("non-direct attribute id: %u", id);
    }
    // TODO
    return { nullptr, nullptr };
}

void OGGraphMutateAttribute(OGAttribute attribute, const OGTypeID type, bool invalidating) {
    // TODO
}

OGAttribute OGGraphGetIndirectDependency(OGAttribute attribute) {
    // TODO
    return OGAttributeNil;
}

void OGGraphSetIndirectDependency(OGAttribute attribute1, OGAttribute attribute2) {
    // TODO
}

OGAttribute OGGraphGetIndirectAttribute(OGAttribute attribute) {
    // TODO
    return OGAttributeNil;
}

void OGGraphSetIndirectAttribute(OGAttribute attribute1, OGAttribute attribute2) {
    // TODO
}

OGAttribute OGGraphCreateAttribute(long index, const void *body, const void * value) {
    // TODO
    return OGAttributeNil;
}

const OGValue OGGraphGetValue(OGAttribute attribute, OGValueOptions options, OGTypeID type) {
    // TODO
    return OGValue { nullptr, false };
}

bool OGGraphSetValue(OGAttribute attribute, const void *value, OGTypeID type) {
    // TODO
    return false;
}

const OGValue OGGraphGetInputValue(OGAttribute attribute, OGAttribute inputAttribute, OGValueOptions options, const OGTypeID type) {
    // TODO
    return OGValue { nullptr, false };
}

const void * _Nullable OGGraphGetOutputValue(OGTypeID type) {
    // TODO
    return nullptr;
}

void OGGraphSetOutputValue(const void *value, const OGTypeID type) {
    // TODO
}

OGValueState OGGraphGetValueState(OGAttribute attribute) {
    // TODO
    return {};
}

bool OGGraphHasValue(OGAttribute attribute) {
    // TODO
    return false;
}

void OGGraphUpdateValue(OGAttribute attribute) {
    // TODO
}

void OGGraphPrefetchValue(OGAttribute attribute) {
    // TODO
}

void OGGraphInvalidateValue(OGAttribute attribute) {
    // TODO
}

void OGGraphVerifyType(OGAttribute attribute, OGTypeID type) {
    // TODO
}

OGGraphRef OGGraphGetAttributeGraph(OGAttribute attribute) {
    // TODO
    return nullptr;
}

OGSubgraphRef OGGraphGetAttributeSubgraph(OGAttribute attribute) {
    // TODO
    return nullptr;
}

const void * OGGraphReadCachedAttribute(long hashValue, OGTypeID bodyType, const void *bodyPointer, OGTypeID valueType, OGCachedValueOptions options, OGAttribute attribute, bool unknown) {
    // TODO
    return nullptr;
}

const void * _Nullable OGGraphReadCachedAttributeIfExists(long hashValue, OGTypeID bodyType, const void *bodyPointer, OGTypeID valueType, OGCachedValueOptions options, OGAttribute attribute, bool unknown) {
    // TODO
    return nullptr;
}

void OGGraphWithUpdate(
    OGAttribute attribute,
    void (* callback)(const void *context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
    const void *context
) {
    // TODO
    callback(context);
}
