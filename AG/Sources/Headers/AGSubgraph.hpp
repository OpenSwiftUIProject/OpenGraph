//
//  AGSubgraph.hpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#ifndef AGSubgraph_hpp
#define AGSubgraph_hpp

#include "AGBase.hpp"
#include "CFRuntime.h"

typedef struct AG_BRIDGED_TYPE(id) AGSubgraphStorage * AGSubgraphRef;

struct AGSubgraphStorage {
    CFRuntimeBase base;
};

// MARK: - Exported C functions

//AG_EXTERN_C_BEGIN
//
//AG_EXPORT
//AG_REFINED_FOR_SWIFT
//AGSubgraphRef AGSubgraphCreate(AGGraphRef graph);
//
//AG_EXPORT
//AG_REFINED_FOR_SWIFT
//AGSubgraphRef AGSubgraphCreate2(AGGraphRef graph);
//
//AG_EXTERN_C_END


#endif /* AGSubgraph_hpp */
