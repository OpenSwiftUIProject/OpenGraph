//
//  GraphDescriptionCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
struct GraphDescriptionCompatibilityTests {
    @Test
    func format() {
        #expect(DescriptionOption.format.rawValue as String == "format")
    }
}
#endif
