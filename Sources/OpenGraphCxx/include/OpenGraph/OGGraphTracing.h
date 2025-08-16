//
//  OGGraphTracing.h
//  OpenGraphCxx

#ifndef OGGraphTracing_hpp
#define OGGraphTracing_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>
#include <OpenGraph/OGUniqueID.h>

typedef OG_OPTIONS(uint32_t, OGGraphTraceOptions) {
    OGGraphTraceOptionsEnabled = 1 << 0,
    OGGraphTraceOptionsFull = 1 << 1,
    OGGraphTraceOptionsBacktrace = 1 << 2,
    OGGraphTraceOptionsPrepare = 1 << 3,
    OGGraphTraceOptionsCustom = 1 << 4,
    OGGraphTraceOptionsAll = 1 << 5,
} OG_SWIFT_NAME(OGGraphRef.TraceOptions);

typedef struct OGTrace *OGTraceRef;

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing(_Nullable OGGraphRef graph, OGGraphTraceOptions options) OG_SWIFT_NAME(OGGraphRef.startTracing(_:options:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing2(_Nullable OGGraphRef graph, OGGraphTraceOptions options, _Nullable CFArrayRef subsystems) OG_SWIFT_NAME(OGGraphRef.startTracing(_:flags:subsystems:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStopTracing(_Nullable OGGraphRef graph) OG_SWIFT_NAME(OGGraphRef.stopTracing(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGGraphAddTrace(OGGraphRef graph, const OGTraceRef trace, void *_Nullable context)
OG_SWIFT_NAME(OGGraphRef.addTrace(self:_:context:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphRemoveTrace(OGGraphRef graph, OGUniqueID trace_id) OG_SWIFT_NAME(OGGraphRef.removeTrace(self:traceID:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphTracing_hpp */
