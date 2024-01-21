//
//  graph.hpp
//
//
//  Created by Kyle on 2024/1/18.
//

#ifndef graph_hpp
#define graph_hpp

#include "OGBase.hpp"
#if TARGET_OS_DARWIN && __OBJC__
@class NSDictionary;
#endif /* TARGET_OS_DARWIN */

namespace OG {
class Graph {
    // TODO
public:
    #if TARGET_OS_DARWIN && __OBJC__
    static CFTypeRef description(const Graph * graph, NSDictionary* dic);
    #endif /* TARGET_OS_DARWIN && __OBJC__ */
}; /* Graph */
} /* OG */

// MARK: - Exported C functions

OG_EXTERN_C_BEGIN

OG_EXPORT
OG_REFINED_FOR_SWIFT
OG::Graph* OGGraphCreate();

OG_EXPORT
OG_REFINED_FOR_SWIFT
OG::Graph* OGGraphCreateShared(void *);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGGraphArchiveJSON(char const* name);

#if TARGET_OS_DARWIN && __OBJC__
OG_EXPORT
OG_REFINED_FOR_SWIFT
CFTypeRef OGGraphDescription(OG::Graph* graph, NSDictionary* options);
#endif /* TARGET_OS_DARWIN && __OBJC__ */

OG_EXTERN_C_END

#endif /* graph_hpp */
