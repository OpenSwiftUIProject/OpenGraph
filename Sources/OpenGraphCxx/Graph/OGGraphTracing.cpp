//
//  OGGraphTracing.mm
//  OpenGraphCxx

#include <OpenGraph/OGGraphTracing.h>

void OGGraphStartTracing(_Nullable OGGraphRef graph, OGGraphTraceOptions options) {
    OGGraphStartTracing2(graph, options, NULL);
}

void OGGraphStartTracing2(_Nullable OGGraphRef graph, OGGraphTraceOptions options, _Nullable CFArrayRef array) {
    // TODO
}

void OGGraphStopTracing(_Nullable OGGraphRef graph) {
    // TODO
}

void OGGraphSyncTracing(_Nullable OGGraphRef graph) {
    // TODO
}

CFStringRef OGGraphCopyTracePath(_Nullable OGGraphRef graph) {
    // TODO
    return nullptr;
}

OGUniqueID OGGraphAddTrace(OGGraphRef graph, const OGTraceRef trace, void *context) {
    // TODO
    return 0;
}

void OGGraphRemoveTrace(OGGraphRef graph, OGUniqueID trace_id) {
    // TODO
}

void OGGraphSetTrace(OGGraphRef graph, const OGTraceRef trace, void *context) {
    // TODO
}

void OGGraphResetTrace(OGGraphRef graph) {
    // TODO
}

bool OGGraphIsTracingActive(OGGraphRef graph) {
    // TODO
    return false;
}

const char *OGGraphGetTraceEventName(uint32_t event_id) {
    // TODO
    return nullptr;
}

const char *OGGraphGetTraceEventSubsystem(uint32_t event_id) {
    // TODO
    return nullptr;
}

uint32_t OGGraphRegisterNamedTraceEvent(const char *event_name, const char *event_subsystem) {
    // TODO
    return 0;
}
