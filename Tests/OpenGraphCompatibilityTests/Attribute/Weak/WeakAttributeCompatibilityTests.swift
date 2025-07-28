//
//  WeakAttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
@Suite(.enabled(if: compatibilityTestEnabled))
final class WeakAttributeCompatibilityTests: AttributeTestBase {
    @Test
    func initTest() {
        let _ = WeakAttribute<Int>()
        let _ = WeakAttribute<Int>(nil)
        let attr = Attribute(value: 0)
        let _ = WeakAttribute(attr)
    }
}
#endif
