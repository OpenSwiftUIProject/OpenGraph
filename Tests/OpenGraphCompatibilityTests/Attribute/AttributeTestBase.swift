//
//  AttributeTestBase.swift
//
//
//

import Testing

/// Base class for Attribute Related test case
class AttributeTestBase {
    private static let sharedGraph = Graph()
    private var graph: Graph
    private var subgraph: Subgraph
    
    init() {
        graph = Graph(shared: Self.sharedGraph)
        subgraph = Subgraph(graph: graph)
        Subgraph.current = subgraph
    }
    
    deinit {
        Subgraph.current = nil
    }
}
