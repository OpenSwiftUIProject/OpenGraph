//
//  OGGraphTracing.h
//  OpenGraphCxx

#ifndef OGGraphTracing_hpp
#define OGGraphTracing_hpp

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>
#include <OpenGraph/OGUniqueID.h>

typedef OG_OPTIONS(uint32_t, OGGraphTraceFlags) {
    OGGraphTraceFlagsEnabled = 1 << 0,
    OGGraphTraceFlagsFull = 1 << 1,
    OGGraphTraceFlagsBacktrace = 1 << 2,
    OGGraphTraceFlagsPrepare = 1 << 3,
    OGGraphTraceFlagsCustom = 1 << 4,
    OGGraphTraceFlagsAll = 1 << 5,
} OG_SWIFT_NAME(OGGraphRef.TraceFlags);

typedef struct OGTrace *OGTraceRef;

OG_ASSUME_NONNULL_BEGIN

OG_IMPLICIT_BRIDGING_ENABLED

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing(_Nullable OGGraphRef graph, OGGraphTraceFlags flags) OG_SWIFT_NAME(OGGraphRef.startTracing(_:flags:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphStartTracing2(_Nullable OGGraphRef graph, OGGraphTraceFlags flags, _Nullable CFArrayRef subsystems) OG_SWIFT_NAME(OGGraphRef.startTracing(_:flags:subsystems:));

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
