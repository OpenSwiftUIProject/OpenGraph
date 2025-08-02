//
//  OGGraphContext.h
//  OpenGraphCxx

#ifndef OGGraphContext_h
#define OGGraphContext_h

#include <OpenGraphC/OGBase.h>
#include <OpenGraphC/OGGraph.h>

// MARK: - Exported C functions

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphContextGetGraph(OGGraphContextRef context) OG_SWIFT_NAME(getter:OGGraphContextRef.graph(self:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphContext_h */
