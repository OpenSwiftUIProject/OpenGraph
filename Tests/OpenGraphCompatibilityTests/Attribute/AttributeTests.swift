//
//  AttributeTests.swift
//  
//
//  Created by Kyle on 2024/2/17.
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
final class AttributeTests: AttributeTestBase {
    @Test
    func initWithValue() throws {
        let intAttribute = Attribute(value: 0)
        #expect(intAttribute.value == 0)
    }
    
    @Test
    func hashableAndEquatable() throws {
        let a = Attribute<Int>(identifier: .nil)
        let b = Attribute<Int>(identifier: .nil)
        #expect(a == b)
        #expect(a.hashValue == b.hashValue)
    }
}
