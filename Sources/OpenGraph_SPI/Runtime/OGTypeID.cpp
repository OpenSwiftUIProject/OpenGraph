//
//  OGTypeID.cpp
//
//
//  Created by Kyle on 2024/1/7.
//

#include "OGTypeID.h"

#ifdef OPENGRAPH_SWIFT_TOOLCHAIN_VERSION
#include <swift/Runtime/Metadata.h>
#endif

OGTypeKind OGTypeGetKind(OGTypeID typeID) {
    #ifdef OPENGRAPH_SWIFT_TOOLCHAIN_VERSION
    const swift::Metadata *type = reinterpret_cast<const swift::Metadata *>(typeID);
    switch (type->getKind()) {
        case swift::MetadataKind::Class:
            return OGTypeKindClass;
        case swift::MetadataKind::Struct:
            return OGTypeKindStruct;
        case swift::MetadataKind::Enum:
            return OGTypeKindEnum;
        case swift::MetadataKind::Optional:
            return OGTypeKindOptional;
        case swift::MetadataKind::Tuple:
            return OGTypeKindTuple;
        case swift::MetadataKind::Function:
            return OGTypeKindFunction;
        case swift::MetadataKind::Existential:
            return OGTypeKindExistential;
        case swift::MetadataKind::Metatype:
            return OGTypeKindMetatype;
        default:
            return OGTypeKindNone;
    }
    #else
    return OGTypeKindNone;
    #endif
}

const void * OGTypeNominalDescriptor(OGTypeID typeID) {
    return nullptr;
}
