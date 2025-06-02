//
//  OptionalAttributeTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
@Suite(.disabled(if: !compatibilityTestEnabled, "OptionalAttribute is not implemented"))
final class OptionalAttributeTests: AttributeTestBase {
    @Test
    func basicInit() {
        let ao1 = AnyOptionalAttribute()
        let o1 = OptionalAttribute<Void>()
        #expect(o1 == OptionalAttribute<Void>(base: ao1))
        
        let attr = Attribute<Void>(identifier: .init(rawValue: 0x1))
        let ao2 = AnyOptionalAttribute(attr.identifier)
        let o2 = OptionalAttribute(attr)
        #expect(o2 == OptionalAttribute<Void>(base: ao2))

        let o3 = OptionalAttribute<Void>(nil)
        #expect(o3.base.identifier == .nil)
    }
    
    @Test(.disabled("crash for invalid data offset"))
    func initWithWeak() {
        let attr = Attribute(value: 0)
        let weakAttr = WeakAttribute(attr)
        let _ = OptionalAttribute(weakAttr)
    }
    
    @Test
    func description() {
        let o1 = OptionalAttribute<Void>()
        #expect(o1.description == "nil")
        
        let attr = AnyAttribute(rawValue: 0x1)
        let o2 = OptionalAttribute(Attribute<Void>(identifier: attr))
        #expect(o2.description == "#1")
    }
}
#endif
