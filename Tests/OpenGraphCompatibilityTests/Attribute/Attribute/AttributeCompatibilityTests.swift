//
//  AttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

#if canImport(Darwin)
@MainActor
@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"), .graphScope)
struct AttributeCompatibilityTests {
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
        value = 3
        #expect(value == 3)
        #expect(_value.setValue(4) == true)
        #expect(value == 4)
        let newAttribute = $value
        value = 5
        #expect(newAttribute.wrappedValue == 5)
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
        #expect(attribute[keyPath: \.third].wrappedValue == value.third)
    }
    
    @Test
    func value() {
        let attribute = Attribute(value: 5)
        #expect(attribute.hasValue == true)
        #expect(attribute.changedValue(options: []) == (5, false))
        
        #expect(attribute.setValue(3) == true)
        #expect(attribute.changedValue(options: []) == (3, false)) // TODO: How to test for changed == true

        // Unknown effect and untested.
        // Just add here for linkage test
        attribute.updateValue()
        attribute.prefetchValue()
        attribute.invalidateValue()
    }
    
    @Test
    func mutateBodyAPI() {
        let attribute = Attribute(value: 5)
        attribute.mutateBody(as: External<Int>.self, invalidating: true) { _ in
            
        }
    }
    
    @Test
    func flagSetter() {
        let attribute = Attribute(value: ())
        attribute.flags = .init(rawValue: 1)
        #expect(attribute.flags == .init(rawValue: 1))
    }
}
#endif
