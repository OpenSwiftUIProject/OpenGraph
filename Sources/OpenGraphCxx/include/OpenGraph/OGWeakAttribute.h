//
//  OGWeakAttribute.h
//  OpenGraphCxx

#ifndef OGWeakAttribute_hpp
#define OGWeakAttribute_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGAttribute.h>
#include <OpenGraph/OGWeakValue.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGWeakAttribute {
    struct {
        OGAttribute identifier;
        uint32_t seed;
    } _details;
} OGWeakAttribute OG_SWIFT_NAME(AnyWeakAttribute);

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGWeakAttribute OGCreateWeakAttribute(OGAttribute attribute);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGWeakAttributeGetAttribute(OGWeakAttribute weakAttribute);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGWeakValue OGGraphGetWeakValue(OGWeakAttribute weakAttribute, OGValueOptions options, OGTypeID type);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGWeakAttribute_h */
