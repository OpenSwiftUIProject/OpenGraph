//
//  IndirectAttributeTests.swift
//
//
//  Created by Kyle on 2024/3/3.
//

import Testing

#if canImport(Darwin)
@Suite(.disabled(if: !compatibilityTestEnabled, "IndirectAttribute is not implemented"))
final class IndirectAttributeTests: AttributeTestBase {
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
