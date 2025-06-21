//
//  GraphDescriptionTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
struct GraphDescriptionTests {
    @Test
    func format() {
        #expect(Graph.descriptionFormat.takeUnretainedValue() as String == "format")
    }
}
#endif
