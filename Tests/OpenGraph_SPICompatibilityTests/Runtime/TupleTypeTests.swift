//
//  TupleTypeTests.swift
//  OpenGraph_SPICompatibilityTests

import Testing

@Suite(.enabled(if: swiftToolchainSupported))
struct TupleTypeTests {
    @Test
    func newTupleType() {
        let elements: [Metadata] = [Metadata(Int.self), Metadata(Double.self), Metadata(String.self)]
        let tupleType = TupleType(count: 3, elements: elements)
        #expect(tupleType.rawValue == Metadata((Int, Double, String).self).rawValue)
    }
}
