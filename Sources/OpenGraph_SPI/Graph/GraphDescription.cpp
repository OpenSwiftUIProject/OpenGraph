//
//  GraphDescription.cpp
//  OpenGraph_SPI

#include "OGGraphDescription.h"
#include "OGGraph.h"
#include "Graph.hpp"
#include "../Util/assert.hpp"

CFTypeRef OGGraphDescription(OGGraphRef graph, CFDictionaryRef options) {
    #if OG_OBJC_FOUNDATION
    if (graph == nullptr) {
        return OG::Graph::description(nullptr, (__bridge NSDictionary*)options);
    }
    if (graph->context.isInvalid()) {
        OG::precondition_failure("invalidated graph");
    }
    return OG::Graph::description(&graph->context.get_graph(), (__bridge NSDictionary*)options);
    #endif
}

void OGGraphArchiveJSON(char const * _Nullable name) {
    #if OG_OBJC_FOUNDATION
    OG::Graph::write_to_file(nullptr, name, 0);
    #endif
}

void OGGraphArchiveJSON2(char const * _Nullable name, uint8_t options) {
    #if OG_OBJC_FOUNDATION
    OG::Graph::write_to_file(nullptr, name, options);
    #endif
}

