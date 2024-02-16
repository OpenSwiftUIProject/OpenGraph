//
//  OGGraphContext.hpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#ifndef OGGraphContext_hpp
#define OGGraphContext_hpp

#include "OGBase.hpp"
#include "OGGraph.hpp"

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGGraphRef OGGraphContextGetGraph(OGGraphContextRef context);

OG_EXTERN_C_END

#endif /* OGGraphContext_hpp */
