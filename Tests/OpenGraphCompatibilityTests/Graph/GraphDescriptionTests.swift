//
//  GraphDescriptionTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct GraphDescriptionTests {
    @Test
    func format() {
        #expect(OGGraph.descriptionFormat.takeUnretainedValue() as String == "format")
    }
}
