//
//  OGTupleType.cpp
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: Complete

#include "OGTupleType.h"
#include "metadata.hpp"
#include "../Util/assert.hpp"

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
#include <swift/Runtime/Metadata.h>
#endif

OGTupleType OGNewTupleType(size_t count, const OGTypeID *elements) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    if (count == 1) {
        return elements[0];
    }
    auto metadata_elements = reinterpret_cast<const Metadata* const*>(elements);
    const auto response = swift_getTupleTypeMetadata(MetadataState::Complete, count, metadata_elements, nullptr, nullptr);
    if (response.State != MetadataState::Complete) {
        OG::precondition_failure("invalid tuple type.");
    }
    return reinterpret_cast<OGTupleType>(response.Value);
    #else
    return nullptr;
    #endif
}

size_t OGTupleCount(OGTupleType tuple_type) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        return 1;
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    return tuple_metadata->NumElements;
    #else
    return 0;
    #endif
}

size_t OGTupleSize(OGTupleType tuple_type) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    return metadata->vw_size();
    #else
    return 0;
    #endif
}

OGTypeID OGTupleElementType(OGTupleType tuple_type, size_t index) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        return reinterpret_cast<OGTypeID>(metadata);
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    return reinterpret_cast<OGTypeID>(element.Type);
    #else
    return nullptr;
    #endif
}

size_t OGTupleElementSize(OGTupleType tuple_type, size_t index) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        return metadata->vw_size();
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    return element.Type->vw_size();
    #else
    return nullptr;
    #endif
}

size_t OGTupleElementOffset(OGTupleType tuple_type, size_t index) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        return 0;
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    return element.Offset;
    #else
    return nullptr;
    #endif
}

size_t OGTupleElementOffsetChecked(OGTupleType tuple_type, size_t index, OGTypeID check_type) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        if (reinterpret_cast<OGTypeID>(metadata) != check_type) {
            OG::precondition_failure("element type mismatch");
        }
        return 0;
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    if (reinterpret_cast<OGTypeID>(element.Type) != check_type) {
        OG::precondition_failure("element type mismatch");
    }
    return element.Offset;
    #else
    return nullptr;
    #endif
}

void *update(void* dst_ptr, const void *src_ptr, const OG::swift::metadata * metadata, OGTupleCopyOptions mode) {
    auto dst = reinterpret_cast<swift::OpaqueValue *>(dst_ptr);
    auto src = reinterpret_cast<swift::OpaqueValue *>(const_cast<void *>(src_ptr));
    switch (mode) {
        case OGTupleCopyOptionsAssignCopy:
            return metadata->vw_assignWithCopy(dst, src);
        case OGTupleCopyOptionsInitCopy:
            return metadata->vw_initializeWithCopy(dst, src);
        case OGTupleCopyOptionsAssignTake:
            return metadata->vw_assignWithTake(dst, src);
        case OGTupleCopyOptionsInitTake:
            return metadata->vw_initializeWithTake(dst, src);
        default:
            OG::precondition_failure("unknown copy options: %d", mode);
    }
}

void *OGTupleSetElement(OGTupleType tuple_type, void* tuple_value, size_t index, const void *element_value, OGTypeID check_type, OGTupleCopyOptions mode) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        if (reinterpret_cast<OGTypeID>(metadata) != check_type) {
            OG::precondition_failure("element type mismatch");
        }
        return update(tuple_value, element_value, metadata, mode);
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    if (reinterpret_cast<OGTypeID>(element.Type) != check_type) {
        OG::precondition_failure("element type mismatch");
    }
    return update((void *)((intptr_t)tuple_value + index), element_value, metadata, mode);
    #else
    return nullptr;
    #endif
}

void *OGTupleGetElement(OGTupleType tuple_type, void* tuple_value, size_t index, void *element_value, OGTypeID check_type, OGTupleCopyOptions mode) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        if (reinterpret_cast<OGTypeID>(metadata) != check_type) {
            OG::precondition_failure("element type mismatch");
        }
        return update(element_value, tuple_value, metadata, mode);
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    if (reinterpret_cast<OGTypeID>(element.Type) != check_type) {
        OG::precondition_failure("element type mismatch");
    }
    return update(element_value, (const void *)((intptr_t)tuple_value + index), metadata, mode);
    #else
    return nullptr;
    #endif
}

void OGTupleDestory(OGTupleType tuple_type, void *value) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    metadata->vw_destroy(reinterpret_cast<swift::OpaqueValue *>(value));
    #endif
}

void OGTupleDestoryElement(OGTupleType tuple_type, void *value, size_t index) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
    auto metadata = reinterpret_cast<OG::swift::metadata const*>(tuple_type);
    if (metadata->getKind() != swift::MetadataKind::Tuple) {
        if (index != 0) {
            OG::precondition_failure("index out of range: %d", index);
        }
        metadata->vw_destroy(reinterpret_cast<swift::OpaqueValue *>(value));
    }
    auto tuple_metadata = reinterpret_cast<const swift::TupleTypeMetadata *>(metadata);
    if (tuple_metadata->NumElements <= index) {
        OG::precondition_failure("index out of range: %d", index);
    }
    auto element = tuple_metadata->getElement(unsigned(index));
    auto element_type = element.Type;
    element_type->vw_destroy(reinterpret_cast<swift::OpaqueValue *>((intptr_t)value + index));
    #endif
}
