//
//  AGGraphContext.h
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef AGGraphContext_h
#define AGGraphContext_h

#include "AGBase.h"
#include "AGGraph.h"

// MARK: - Exported C functions

AG_ASSUME_NONNULL_BEGIN

AG_EXTERN_C_BEGIN

AG_EXPORT
AG_REFINED_FOR_SWIFT
AGGraphRef AGGraphContextGetGraph(AGGraphContextRef context) AG_SWIFT_NAME(getter:AGGraphContextRef.graph(self:));

AG_EXTERN_C_END

AG_ASSUME_NONNULL_END

#endif /* AGGraphContext_h */
