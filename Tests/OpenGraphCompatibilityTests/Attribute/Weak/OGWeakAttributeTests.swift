//
//  AnyWeakAttributeTests.swift
//
//
//  Created by Kyle on 2024/3/4.
//

import Testing

#if canImport(Darwin)
final class AnyWeakAttributeTests: AttributeTestBase {
    @Test
    func basic() {
        let w1 = AnyWeakAttribute(nil)
        let w2 = AnyWeakAttribute(WeakAttribute<Void>(nil))
        #expect(w1.attribute == nil)
        #expect(w2.attribute == nil)
        #expect(w2.unsafeCast(to: Void.self) == WeakAttribute(base: w2))
    }
    
    @Test
    func hashable() {
        let w1 = AnyWeakAttribute(nil)
        let w2 = AnyWeakAttribute(WeakAttribute<Void>(nil))
        #expect(w1 == w2)
        _ = w1.hashValue
    }
    
    @Test
    func description() {
        let attr = Attribute<Int>(value: 1)
        if compatibilityTestEnabled {
            #expect(AnyWeakAttribute(attr.identifier).description != "nil")            
        }
        #expect(AnyWeakAttribute(nil).description == "nil")
    }
}
#endif
