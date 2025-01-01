//
//  OGTupleType.h
//  OpenGraph_SPI
//
//  Audited for iOS 18.0
//  Status: Complete

#ifndef OGTupleType_h
#define OGTupleType_h

#include "OGBase.h"
#include "OGTypeID.h"

OG_ASSUME_NONNULL_BEGIN

typedef const OGSwiftMetadata *OGTupleType OG_SWIFT_STRUCT OG_SWIFT_NAME(TupleType);

typedef OG_CLOSED_ENUM(uint32_t, OGTupleCopyOptions) {
    OGTupleCopyOptionsAssignCopy = 0,
    OGTupleCopyOptionsInitCopy = 1,
    OGTupleCopyOptionsAssignTake = 2,
    OGTupleCopyOptionsInitTake = 3
} OG_SWIFT_NAME(TupleType.CopyOptions);

struct OGUnsafeTuple {
    OGTupleType type;
    const void *value;
} OG_SWIFT_NAME(UnsafeTuple);

typedef struct OGUnsafeTuple OGUnsafeTuple;

struct OGUnsafeMutableTuple {
    OGTupleType type;
    void *value;
} OG_SWIFT_NAME(UnsafeMutableTuple);

typedef struct OGUnsafeMutableTuple OGUnsafeMutableTuple;

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTupleType OGNewTupleType(size_t count, const OGTypeID _Nonnull * _Nonnull elements) OG_SWIFT_NAME(TupleType.init(count:elements:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
size_t OGTupleCount(OGTupleType tuple_type) OG_SWIFT_NAME(getter:TupleType.count(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
size_t OGTupleSize(OGTupleType tuple_type) OG_SWIFT_NAME(getter:TupleType.size(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeID OGTupleElementType(OGTupleType tuple_type, size_t index) OG_SWIFT_NAME(TupleType.elementType(self:at:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
size_t OGTupleElementSize(OGTupleType tuple_type, size_t index) OG_SWIFT_NAME(TupleType.elementSize(self:at:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
size_t OGTupleElementOffset(OGTupleType tuple_type, size_t index) OG_SWIFT_NAME(TupleType.elementOffset(self:at:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
size_t OGTupleElementOffsetChecked(OGTupleType tuple_type, size_t index, OGTypeID check_type) OG_SWIFT_NAME(TupleType.elementOffset(self:at:type:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void *OGTupleSetElement(OGTupleType tuple_type, void* tuple_value, size_t index, const void *element_value, OGTypeID check_type, OGTupleCopyOptions mode);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void *OGTupleGetElement(OGTupleType tuple_type, void* tuple_value, size_t index, void *element_value, OGTypeID check_type, OGTupleCopyOptions mode);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTupleDestory(OGTupleType tuple_type, void *buffer) OG_SWIFT_NAME(TupleType.destory(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTupleDestoryElement(OGTupleType tuple_type, void *buffer, size_t index) OG_SWIFT_NAME(TupleType.destory(self:_:at:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGTupleWithBuffer(OGTupleType tuple_type, size_t count, const void (*_Nullable function)(const void * _Nullable context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift), const void * _Nullable context);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGTupleType_h */
