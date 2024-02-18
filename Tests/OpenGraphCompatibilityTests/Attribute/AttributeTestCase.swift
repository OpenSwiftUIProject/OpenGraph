//
//  AttributeTestCase.swift
//  
//
//  Created by Kyle on 2024/2/18.
//

import XCTest

/// Base class for Attribute Related test case
class AttributeTestCase: XCTestCase {
    private static let sharedGraph = OGGraph()
    private static var graph: OGGraph!
    private static var subgraph: OGSubgraph!
    
    override class func setUp() {
        let sharedGraph = OGGraph()
        let graph = OGGraph(shared: sharedGraph)
        let subgraph = OGSubgraph(graph: graph)
        OGSubgraph.current = subgraph
        
        self.graph = graph
        self.subgraph = subgraph
    }
    
    override class func tearDown() {
        OGSubgraph.current = nil
    }
}
