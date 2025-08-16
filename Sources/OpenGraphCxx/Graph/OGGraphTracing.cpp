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
