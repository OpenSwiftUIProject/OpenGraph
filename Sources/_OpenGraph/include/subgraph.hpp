//
//  subgraph.hpp
//  
//
//  Created by Kyle on 2024/2/15.
//

#ifndef subgraph_hpp
#define subgraph_hpp

#include "OGBase.hpp"
#include "AttributeID.hpp"
#include "graph.hpp"

// https://github.com/apple/swift/blob/main/docs/CToSwiftNameTranslation.md#cf-types
typedef struct OG_BRIDGED_TYPE(id) OGSubgraphStorage * OGSubgraphRef;

namespace OG {
class SubgraphObject;

class Subgraph final {
    // TODO
public:
    static Subgraph &from_cf(OGSubgraphRef graph) OG_NOEXCEPT;
    static Subgraph &to_cf() OG_NOEXCEPT;
    
    Subgraph(SubgraphObject*, OG::Graph::Context&, OG::AttributeID);
}; /* Subgraph */
} /* OG */


#endif /* subgraph_hpp */
