//
//  AttributeTests.swift
//
//
//  Created by Kyle on 2024/2/17.
//

import Testing

#if canImport(Darwin)
@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
final class AttributeTests: AttributeTestBase {
    @Test
    func initWithValue() {
        let intAttribute = Attribute(value: 0)
        #expect(intAttribute.value == 0)
    }
    
    @Test
    func hashableAndEquatable() {
        let a = Attribute<Int>(identifier: .nil)
        let b = Attribute<Int>(identifier: .nil)
        #expect(a == b)
        #expect(a.hashValue == b.hashValue)
    }
    
    @Test
    func propertyWrapper() {
        @Attribute(value: 0) var value
        #expect(value == 0)
//        value = 3
//        #expect(value == 3)
        
        let newAttribute = $value
//        value = 5
        #expect(newAttribute.wrappedValue == 0/*5*/)
    }
    
    @Test
    func value() {
        let attribute = Attribute(value: 5)
        #expect(attribute.changedValue(options: []) == (5, false))
    }
}
#endif
