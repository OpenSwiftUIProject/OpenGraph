//
//  MapCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing
import OpenGraphTestsSupport

@MainActor
@Suite(.disabled(if: !compatibilityTestEnabled), .graphScope)
struct MapCompatibilityTests {
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
