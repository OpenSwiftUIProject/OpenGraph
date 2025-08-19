//
//  IndirectAttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing
import OpenGraphTestsSupport

#if canImport(Darwin)
@MainActor
@Suite(.disabled(if: !compatibilityTestEnabled, "IndirectAttribute is not implemented"), .graphScope)
struct IndirectAttributeCompatibilityTests {
    @Test
    func basic() {
        let source = Attribute(value: 0)
        let indirect = IndirectAttribute(source: source)
        #expect(indirect.identifier != source.identifier)
        #expect(indirect.source.identifier == source.identifier)
        #expect(indirect.dependency == .init(rawValue: 0))
    }
}
#endif
