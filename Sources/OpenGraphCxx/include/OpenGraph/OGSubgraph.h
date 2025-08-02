//
//  OGSubgraph.h
//  OpenGraphCxx

#ifndef OGSubgraph_h
#define OGSubgraph_h

#include <OpenGraph/OGAttribute.h>
#include <OpenGraph/OGAttributeFlags.h>
#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>
#include <OpenGraph/OGUniqueID.h>
#include <OpenGraph/Private/CFRuntime.h>

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeID OGSubgraphGetTypeID();

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate(OGGraphRef cf_graph) OG_SWIFT_NAME(OGSubgraphRef.init(graph:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGSubgraphRef OGSubgraphCreate2(OGGraphRef cf_graph, OGAttribute attribute) OG_SWIFT_NAME(OGSubgraphRef.init(graph:attribute:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
_Nullable OGSubgraphRef OGSubgraphGetCurrent(void) OG_SWIFT_NAME(getter:OGSubgraphRef.current());

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphSetCurrent(_Nullable OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(setter:OGSubgraphRef.current(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
_Nullable OGGraphContextRef OGSubgraphGetCurrentGraphContext(void) OG_SWIFT_NAME(getter:OGSubgraphRef.currentGraphContext());

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphInvalidate(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(OGSubgraphRef.invalidate(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphIsValid(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(getter:OGSubgraphRef.isValid(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGSubgraphGetGraph(OGSubgraphRef cf_subgraph) OG_SWIFT_NAME(getter:OGSubgraphRef.graph(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphAddChild(OGSubgraphRef parent, OGSubgraphRef child) OG_SWIFT_NAME(OGSubgraphRef.addChild(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphAddChild2(OGSubgraphRef parent, OGSubgraphRef child, uint8_t tag) OG_SWIFT_NAME(OGSubgraphRef.addChild(self:_:tag:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphRemoveChild(OGSubgraphRef parent, OGSubgraphRef child) OG_SWIFT_NAME(OGSubgraphRef.removeChild(self:_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphIntersects(OGSubgraphRef subgraph, OGAttributeFlags flags) OG_SWIFT_NAME(OGSubgraphRef.intersects(self:flags:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphApply(OGSubgraphRef cf_subgraph,
                     OGAttributeFlags flags,
                     const void (*function)(const void * _Nullable context OG_SWIFT_CONTEXT, OGAttribute attribute) OG_SWIFT_CC(swift),
                     const void * _Nullable context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphUpdate(OGSubgraphRef cf_subgraph, OGAttributeFlags flags) OG_SWIFT_NAME(OGSubgraphRef.update(self:flags:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphIsDirty(OGSubgraphRef cf_subgraph, OGAttributeFlags flags) OG_SWIFT_NAME(OGSubgraphRef.isDirty(self:flags:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGSubgraphAddObserver(OGSubgraphRef cf_subgraph,
                           const void (*function)(const void * _Nullable context OG_SWIFT_CONTEXT) OG_SWIFT_CC(swift),
                           const void * _Nullable context);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGSubgraphShouldRecordTree(void) OG_SWIFT_NAME(getter:OGSubgraphRef.shouldRecordTree());

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphSetShouldRecordTree(void) OG_SWIFT_NAME(OGSubgraphRef.setShouldRecordTree());

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphBeginTreeElement(OGAttribute attribute, OGTypeID type, uint32_t flags);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphAddTreeValue(OGAttribute attribute, OGTypeID type, const char * key, uint32_t flags);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGSubgraphEndTreeElement(OGAttribute attribute);

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGSubgraph_h */
