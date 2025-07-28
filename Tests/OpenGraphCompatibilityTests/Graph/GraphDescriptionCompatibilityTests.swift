//
//  GraphDescriptionCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
struct GraphDescriptionCompatibilityTests {
    @Test
    func format() {
        #expect(Graph.descriptionFormat as String == "format")
    }
}
#endif
