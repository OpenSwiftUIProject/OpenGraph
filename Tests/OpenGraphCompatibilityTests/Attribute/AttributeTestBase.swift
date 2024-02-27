//
//  AttributeTestBase.swift
//
//
//

import Testing

/// Base class for Attribute Related test case
class AttributeTestBase {
    private static let sharedGraph = OGGraph()
    private var graph: OGGraph
    private var subgraph: OGSubgraph
    
    init() {
        graph = OGGraph(shared: Self.sharedGraph)
        subgraph = OGSubgraph(graph: graph)
        OGSubgraph.current = subgraph
    }
    
    deinit {
        OGSubgraph.current = nil
    }
}
