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
        #expect(newAttribute.wrappedValue == 0 /* 5 */ )
    }
    
    @Test(arguments: [
        Triple(first: 0, second: 1, third: 2),
        Triple(first: 3, second: 4, third: 5),
    ])
    func attributeWithSubscript(_ value: Triple<Int, Int, Int>) {
        let attribute = Attribute(value: value)
        let offsetValue = attribute[offset: { _ in
            PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 8)
        }]
        #expect(offsetValue.wrappedValue == value.second)
        #expect(attribute.first.wrappedValue == value.first)
        #expect(attribute[keyPath: \.third].wrappedValue == value.second)
    }
    
    @Test
    func value() {
        let attribute = Attribute(value: 5)
        #expect(attribute.changedValue(options: []) == (5, false))
    }
}
#endif
