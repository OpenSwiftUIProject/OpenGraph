//
//  OGAttributeType.h
//  OpenGraphCxx

#ifndef OGAttributeType_h
#define OGAttributeType_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGAttributeTypeFlags.h>
#include <OpenGraph/OGClosure.h>
#include <OpenGraph/OGTypeID.h>

OG_ASSUME_NONNULL_BEGIN

typedef struct OGAttributeType OGAttributeType;

typedef struct OGAttributeVTable {
    unsigned long version;
    void (*_Nullable type_destroy)(OGAttributeType *);
    void (*_Nullable self_destroy)(const OGAttributeType *, void *);
    CFStringRef _Nullable (*_Nullable self_description)(const OGAttributeType *, const void *);
    CFStringRef _Nullable (*_Nullable value_description)(const OGAttributeType *, const void *);
    void (*_Nullable update_default)(const OGAttributeType *, void *);
} OGAttributeVTable OG_SWIFT_NAME(_AttributeVTable);

typedef struct OG_SWIFT_NAME(AttributeType) OGAttributeType {
    OGTypeID self_id;
    OGTypeID value_id;
    OGClosureStorage update;
    const OGAttributeVTable *vtable;
    OGAttributeTypeFlags flags;

    uint32_t internal_offset;
    const unsigned char *_Nullable value_layout;

    struct {
        OGTypeID type_id;
        const void *witness_table;
    } body_conformance;
} OGAttributeType;

OG_ASSUME_NONNULL_END

#endif /* OGAttributeType_h */
