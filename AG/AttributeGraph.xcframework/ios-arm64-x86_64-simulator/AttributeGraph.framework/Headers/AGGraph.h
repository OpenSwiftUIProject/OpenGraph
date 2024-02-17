//
//  AGGraph.h
//
//
//  Created by Kyle on 2024/2/5.
//

#ifndef AGGraph_h
#define AGGraph_h

#include "AGBase.h"
#include "CFRuntime.h"

typedef struct AG_BRIDGED_TYPE(id) AGGraphStorage * AGGraphRef;
typedef struct AG_BRIDGED_TYPE(id) AGGraphContextStorage * AGGraphContextRef;
typedef struct AG_BRIDGED_TYPE(id) AGSubgraphStorage * AGSubgraphRef;

struct AGGraphStorage;
struct AGGraphContextStorage;
struct AGSubgraphStorage;

AG_ASSUME_NONNULL_BEGIN

// MARK: - Exported C functions

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreate(void) AG_SWIFT_NAME(AGGraphRef.init());

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphCreateShared(_Nullable AGGraphRef graph) AG_SWIFT_NAME(AGGraphRef.init(shared:));

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

AG_ASSUME_NONNULL_END

#endif /* AGGraph_h */
