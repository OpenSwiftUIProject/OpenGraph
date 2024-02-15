//
//  OGGraph.h
//
//
//  Created by Kyle on 2024/2/5.
//

#ifndef OGGraph_h
#define OGGraph_h

#include "OGBase.hpp"
#include "graph.hpp"
#include "../Private/CFRuntime.h"

// https://github.com/apple/swift/blob/main/docs/CToSwiftNameTranslation.md#cf-types
typedef struct OG_BRIDGED_TYPE(id) OGGraphStorage * OGGraphRef;

struct OGGraphStorage {
    // 0x0
    CFRuntimeBase base;
    // 0x10
    OG::Graph *graph;
    // 0x18
    // TODO
    // 0x58
    bool invalid;
};

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphCreate();

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphCreateShared(OGGraphRef graph);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON(char const* name);

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeRef OGGraphDescription(OG::Graph* graph, CFDictionaryRef options);

OG_EXTERN_C_END


#endif /* OGGraph_h */
