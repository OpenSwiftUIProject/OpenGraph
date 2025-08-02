//
//  OGGraphTracing.h
//  OpenGraphCxx

#ifndef OGGraphTracing_hpp
#define OGGraphTracing_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>

typedef OG_OPTIONS(uint32_t, OGGraphTraceFlags) {
    OGGraphTraceFlags_0 = 0,
    OGGraphTraceFlags_1 = 1 << 0,
    OGGraphTraceFlags_2 = 1 << 1,
} OG_SWIFT_NAME(OGGraphRef.TraceFlags);

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing(_Nullable OGGraphRef graph, OGGraphTraceFlags options) OG_SWIFT_NAME(OGGraphRef.startTracing(_:options:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing2(_Nullable OGGraphRef graph, OGGraphTraceFlags options, _Nullable CFArrayRef array);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStopTracing(_Nullable OGGraphRef graph) OG_SWIFT_NAME(OGGraphRef.stopTracing(_:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphTracing_hpp */
