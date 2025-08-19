//
//  WeakAttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
@MainActor
@Suite(.enabled(if: compatibilityTestEnabled), .graphScope)
struct WeakAttributeCompatibilityTests {
    @Test
    func initTest() {
        let _ = WeakAttribute<Int>()
        let _ = WeakAttribute<Int>(nil)
        let attr = Attribute(value: 0)
        let _ = WeakAttribute(attr)
    }
}
#endif
