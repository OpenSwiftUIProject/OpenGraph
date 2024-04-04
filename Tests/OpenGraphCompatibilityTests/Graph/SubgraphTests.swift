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
}
