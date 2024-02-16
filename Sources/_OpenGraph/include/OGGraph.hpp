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
#include "graph-context.hpp"
#include "../Private/CFRuntime.h"

struct OGGraphStorage {
    CFRuntimeBase base;
    OG::Graph::Context context;
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
CFTypeRef OGGraphDescription(OGGraphRef graph, CFDictionaryRef options);

OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeID OGGraphGetTypeID();

OG_EXTERN_C_END


#endif /* OGGraph_h */
