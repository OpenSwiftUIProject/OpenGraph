//
//  OGGraphContext.h
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef OGGraphContext_h
#define OGGraphContext_h

#include "OGBase.h"
#include "OGGraph.h"

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphContextGetGraph(OGGraphContextRef context);

OG_EXTERN_C_END

#endif /* OGGraphContext_h */
