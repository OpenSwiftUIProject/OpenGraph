//
//  SubgraphTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct SubgraphTests {
    @Test
    func shouldRecordTree() {
        let key = compatibilityTestEnabled ? "AG_TREE" : "OG_TREE"
        setenv(key, "0", 1)
        #expect(OGSubgraph.shouldRecordTree == false)
        
        OGSubgraph.setShouldRecordTree()
        #expect(OGSubgraph.shouldRecordTree == true)
    }
    
    @Test
    func treeElementAPICheck() {
        let graph = OGGraph()
        let subgraph = OGSubgraph(graph: graph)
        subgraph.apply {
            let value = Attribute(value: ())
            OGSubgraph.beginTreeElement(value: value, flags: 0)
            OGSubgraph.addTreeValue(value, forKey: "", flags: 0)
            OGSubgraph.endTreeElement(value: value)
        }
    }
}
