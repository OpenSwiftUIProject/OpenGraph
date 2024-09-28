//
//  AnyOptionalAttributeTests.swift
//
//
//  Created by Kyle on 2024/3/3.
//

import Testing

#if canImport(Darwin)
@Suite(.disabled(if: !compatibilityTestEnabled, "AnyOptionalAttribute is not implemented"))
final class AnyOptionalAttributeTests: AttributeTestBase {
    @Test
    func basicInit() {
        let o1 = AnyOptionalAttribute()
        #expect(o1.identifier == .nil)
        
        let attr = AnyAttribute(rawValue: 0x1)
        let o2 = AnyOptionalAttribute(attr)
        #expect(o2.identifier == attr)
        
        let o3 = AnyOptionalAttribute(nil)
        #expect(o3.identifier == .nil)
    }
    
    @Test
    func attribute() {
        let o1 = AnyOptionalAttribute()
        #expect(o1.attribute == nil)
        
        let attr = AnyAttribute(rawValue: 0x1)
        let o2 = AnyOptionalAttribute(attr)
        #expect(o2.attribute != nil)
    }
    
    @Test
    func current() {
        let currentNil = AnyOptionalAttribute.current
        #expect(currentNil.identifier == .nil)
    }
    
    @Test
    func description() {
        let o1 = AnyOptionalAttribute()
        #expect(o1.description == "nil")
        
        let attr = AnyAttribute(rawValue: 0x1)
        let o2 = AnyOptionalAttribute(attr)
        #expect(o2.description == "#1")
    }
    
    @Test("Test symbol link")
    func other() {
        let optional = OptionalAttribute<Void>()
        let anyOptional = AnyOptionalAttribute(optional)
        _ = anyOptional.unsafeCast(to: Int.self)
        _ = anyOptional.map { _ in 0 }
    }
}
#endif
