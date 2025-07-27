//
//  GraphDescriptionTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
struct GraphDescriptionTests {
    @Test
    func format() {
        #expect(Graph.descriptionFormat as String == "format")
    }
}
#endif
