//
//  OGTreeElement.h
//  OpenGraphCxx

#ifndef OGTreeElement_h
#define OGTreeElement_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGTreeValue.h>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

typedef struct _OGTreeElement *OGTreeElement OG_SWIFT_STRUCT OG_SWIFT_NAME(TreeElement);

typedef struct OGTreeElementValueIterator {
    uintptr_t parent_elt;
    uintptr_t next_elt;
} OG_SWIFT_NAME(Values) OGTreeElementValueIterator;

typedef struct OGTreeElementNodeIterator {
    uintptr_t elt;
    unsigned long node_index;
} OG_SWIFT_NAME(Nodes) OGTreeElementNodeIterator;

typedef struct OGTreeElementChildIterator {
    uintptr_t parent_elt;
    uintptr_t next_elt;
    size_t subgraph_index;
} OG_SWIFT_NAME(Children) OGTreeElementChildIterator;

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeID OGTreeElementGetType(OGTreeElement tree_element) OG_SWIFT_NAME(getter:OGTreeElement.type(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGTreeElementGetValue(OGTreeElement tree_element);

OG_EXPORT
OG_REFINED_FOR_SWIFT
uint32_t OGTreeElementGetFlags(OGTreeElement tree_element) OG_SWIFT_NAME(getter:OGTreeElement.flags(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeElement _Nullable OGTreeElementGetParent(OGTreeElement tree_element)
    OG_SWIFT_NAME(getter:OGTreeElement.parent(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeElementValueIterator OGTreeElementMakeValueIterator(OGTreeElement tree_element)
    OG_SWIFT_NAME(getter:OGTreeElement.values(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeValue _Nullable OGTreeElementGetNextValue(OGTreeElementValueIterator *iter)
    OG_SWIFT_NAME(OGTreeElementValueIterator.next(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeElementNodeIterator OGTreeElementMakeNodeIterator(OGTreeElement tree_element)
    OG_SWIFT_NAME(getter:OGTreeElement.nodes(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGAttribute OGTreeElementGetNextNode(OGTreeElementNodeIterator *iter);

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeElementChildIterator OGTreeElementMakeChildIterator(OGTreeElement tree_element)
    OG_SWIFT_NAME(getter:OGTreeElement.children(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTreeElement _Nullable OGTreeElementGetNextChild(OGTreeElementChildIterator *iter)
    OG_SWIFT_NAME(OGTreeElementChildIterator.next(self:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGTreeElement_h */
