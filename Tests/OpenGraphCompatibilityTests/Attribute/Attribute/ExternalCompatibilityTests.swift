//
//  ExternalCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing
import OpenGraphTestsSupport

// *** Program crashed: Bad pointer dereference at 0x0000000ffff9400a ***
// swift-testing framework will crash here on Linux
// Report to upstream for investigation when we bump to 5.10
#if canImport(Darwin)
@MainActor
@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"), .graphScope)
struct ExternalCompatibilityTests {
    @Test
    func example() throws {
        let type = External<Int>.self
        let externalInt = type.init()
        #expect(externalInt.description == "Int")
        #expect(type.comparisonMode == .equatableAlways)
        #expect(type.flags == [])
    }
}
#endif
