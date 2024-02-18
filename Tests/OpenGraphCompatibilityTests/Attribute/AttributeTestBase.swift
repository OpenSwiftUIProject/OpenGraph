//
//  AttributeTestBase.swift
//
//
//  Created by Kyle on 2024/2/18.
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
