//
//  MapCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled))
final class MapCompatibilityTests: AttributeTestBase {
    @Test
    func description() throws {
        let map = Map(.init(value: 2)) { $0.description }
        let map2 = Map(.init(value: 1)) { $0 + 2 }

        #expect(map.description == "λ String")
        #expect(map2.description == "λ Int")
    }

    @Test
    func value() throws {
        let map = Map(.init(value: 2)) { $0.description }
        let map2 = Map(.init(value: 1)) { $0 + 2 }

        #expect(map.value == "2")
        #expect(map2.value == 3)
    }
}
