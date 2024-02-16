//
//  AGGraph.h
//
//
//  Created by Kyle on 2024/2/5.
//

#ifndef AGGraph_h
#define AGGraph_h

#include "AGBase.hpp"
#include "CFRuntime.h"

typedef struct AG_BRIDGED_TYPE(id) AGGraphStorage * AGGraphRef;

struct AGGraphStorage {
    CFRuntimeBase base;
};

// MARK: - Exported C functions

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreate();

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreateShared(AGGraphRef graph);

AG_EXPORT
AG_REFINED_FOR_SWIFT
void AGGraphArchiveJSON(char const* name);

AG_EXPORT
AG_REFINED_FOR_SWIFT
CFTypeRef AGGraphDescription(AGGraphRef graph, CFDictionaryRef options);

AG_EXPORT
AG_REFINED_FOR_SWIFT
CFTypeID AGGraphGetTypeID();

AG_EXTERN_C_END


#endif /* AGGraph_h */
