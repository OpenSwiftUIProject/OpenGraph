//
//  OGTreeValue.h
//  OpenGraphCxx

#ifndef OGTreeValue_h
#define OGTreeValue_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGAttribute.h>
#include <OpenGraph/OGTypeID.h>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

typedef struct _OGTreeValue *OGTreeValue OG_SWIFT_STRUCT OG_SWIFT_NAME(TreeValue);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeID OGTreeValueGetType(OGTreeValue tree_value) OG_SWIFT_NAME(getter:OGTreeValue.type(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGTreeValueGetValue(OGTreeValue tree_value) OG_SWIFT_NAME(getter:OGTreeValue.value(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const char *OGTreeValueGetKey(OGTreeValue tree_value) OG_SWIFT_NAME(getter:OGTreeValue.key(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
uint32_t OGTreeValueGetFlags(OGTreeValue tree_value) OG_SWIFT_NAME(getter:OGTreeValue.flags(self:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGTreeValue_h */
