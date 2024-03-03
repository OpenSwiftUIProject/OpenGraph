//
//  OGWeakAttributeTests.swift
//
//
//  Created by Kyle on 2024/3/4.
//

import Testing

#if canImport(Darwin)
final class OGWeakAttributeTests: AttributeTestBase {
    @Test
    func basic() {
        let w1 = OGWeakAttribute(nil)
        let w2 = OGWeakAttribute(WeakAttribute<Void>(nil))
        #expect(w1.attribute == nil)
        #expect(w2.attribute == nil)
        #expect(w2.unsafeCast(to: Void.self) == WeakAttribute(base: w2))
    }
    
    @Test
    func hashable() {
        let w1 = OGWeakAttribute(nil)
        let w2 = OGWeakAttribute(WeakAttribute<Void>(nil))
        #expect(w1 == w2)
        _ = w1.hashValue
    }
    
    @Test
    func description() {
        let attr = Attribute<Int>(value: 1)
        if compatibilityTestEnabled {
            #expect(OGWeakAttribute(attr.identifier).description != "nil")            
        }
        #expect(OGWeakAttribute(nil).description == "nil")
    }
}
#endif
