//
//  SubgraphCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

@Suite(.enabled(if: compatibilityTestEnabled))
struct SubgraphCompatibilityTests {
    @Test
    func shouldRecordTree() {
        let key = compatibilityTestEnabled ? "AG_TREE" : "OG_TREE"
        setenv(key, "0", 1)
        #expect(Subgraph.shouldRecordTree == false)
        
        Subgraph.setShouldRecordTree()
        #expect(Subgraph.shouldRecordTree == true)
    }
    
    @Test
    func treeElementAPICheck() {
        let graph = Graph()
        let subgraph = Subgraph(graph: graph)
        subgraph.apply {
            let value = Attribute(value: ())
            Subgraph.beginTreeElement(value: value, flags: 0)
            Subgraph.addTreeValue(value, forKey: "", flags: 0)
            Subgraph.endTreeElement(value: value)
        }
    }
}
