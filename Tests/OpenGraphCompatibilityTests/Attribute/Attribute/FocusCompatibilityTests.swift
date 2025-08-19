//
//  FocusCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing
import OpenGraphTestsSupport

#if canImport(Darwin)
@MainActor
@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"), .graphScope)
struct FocusCompatibilityTests {
    struct Demo {
        var a: Int
        var b: Double
    }
    
    @Test
    func example() throws {
        let root = Attribute<Demo>(value: Demo(a: 0, b: 1.0))
        let type = Focus<Demo, Int>.self
        let focus = type.init(root: root, keyPath: \.a)
        let d = focus.description
        #expect(d == "• Int")
        #expect(focus.value == 0)
        #expect(type.flags == [])
    }
}
#endif
