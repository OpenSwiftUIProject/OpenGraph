//
//  OGGraphTracing.mm
//  OpenGraphCxx

#include "OGGraphTracing.h"

void OGGraphStartTracing(_Nullable OGGraphRef graph, OGGraphTraceFlags options) {
    OGGraphStartTracing2(graph, options, NULL);
}

void OGGraphStartTracing2(_Nullable OGGraphRef graph, OGGraphTraceFlags options, _Nullable CFArrayRef array) {
    // TODO
}

void OGGraphStopTracing(_Nullable OGGraphRef graph) {
    // TODO
}
