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
void OGGraphSyncTracing(_Nullable OGGraphRef graph) OG_SWIFT_NAME(OGGraphRef.syncTracing(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFStringRef OGGraphCopyTracePath(_Nullable OGGraphRef graph) OG_SWIFT_NAME(OGGraphRef.tracePath(_:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGUniqueID OGGraphAddTrace(OGGraphRef graph, const OGTraceRef trace, void *_Nullable context) OG_SWIFT_NAME(OGGraphRef.addTrace(self:_:context:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphRemoveTrace(OGGraphRef graph, OGUniqueID trace_id) OG_SWIFT_NAME(OGGraphRef.removeTrace(self:traceID:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphSetTrace(OGGraphRef graph, const OGTraceRef trace, void *_Nullable context) OG_SWIFT_NAME(OGGraphRef.setTrace(self:_:context:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphResetTrace(OGGraphRef graph) OG_SWIFT_NAME(OGGraphRef.resetTrace(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGGraphIsTracingActive(OGGraphRef graph) OG_SWIFT_NAME(getter:OGGraphRef.isTracingActive(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const char *_Nullable OGGraphGetTraceEventName(uint32_t event_id) OG_SWIFT_NAME(OGGraphRef.traceEventName(for:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const char *_Nullable OGGraphGetTraceEventSubsystem(uint32_t event_id) OG_SWIFT_NAME(OGGraphRef.traceEventSubsystem(for:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
uint32_t OGGraphRegisterNamedTraceEvent(const char *event_name, const char *event_subsystem) OG_SWIFT_NAME(OGGraphRef.registerNamedTraceEvent(name:subsystem:));

OG_EXTERN_C_END

OG_IMPLICIT_BRIDGING_DISABLED

OG_ASSUME_NONNULL_END

#endif /* OGGraphTracing_hpp */
