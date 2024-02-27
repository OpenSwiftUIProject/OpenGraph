//
//  TupleTypeTests.swift
//  
//
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "OGTupleType is not implemented"))
struct TupleTypeTests {
    @Test
    func example() {
        let value = (3, 5.0)
        let tupleType = OGTupleType(type(of: value))
        #expect(tupleType.count == 2)
        #expect(tupleType.size == 16)
        #expect(tupleType.type(at: 0) == Int.self)
        #expect(tupleType.offset(at: 0) == 0)
        
        #expect(tupleType.type(at: 1) == Double.self)
        #expect(tupleType.offset(at: 1) == 8)
    }
}
