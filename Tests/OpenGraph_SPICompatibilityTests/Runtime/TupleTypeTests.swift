//
//  TupleTypeTests.swift
//  OpenGraph_SPICompatibilityTests

import Testing

@Suite(.enabled(if: swiftToolchainSupported))
struct TupleTypeTests {
    class T1 {
        var a = 0
        var b: Double = 0
    }
    
    struct T2 {
        var a: Int
        var b: Double
    }
    
    enum T3 {
        case a, b
    }
    
    @Test
    func newTupleType() {
        let elements: [Metadata] = [Metadata(T1.self), Metadata(T2.self), Metadata(T3.self)]
        let tupleType = TupleType(count: 3, elements: elements)
        #expect(tupleType.rawValue == Metadata((T1, T2, T3).self).rawValue)
    }
    
    @Test
    func tupleCount() {
        #expect(TupleType(T1.self).count == 1)
        #expect(TupleType([T1.self, T2.self]).count == 2)
        #expect(TupleType([T1.self, T2.self, T3.self]).count == 3)
    }
    
    @Test
    func tupleSize() {
        #expect(TupleType(T1.self).size == 8)
        #expect(TupleType([T1.self, T2.self]).size == 24)
        #expect(TupleType([T1.self, T2.self, T3.self]).size == 25)
    }
    
    @Test
    func tupleElement() {
        let tupleType = TupleType([T1.self, T2.self, T3.self])
        #expect(tupleType.elementType(at: 0) == Metadata(T1.self))
        #expect(tupleType.elementType(at: 1) == Metadata(T2.self))
        #expect(tupleType.elementType(at: 2) == Metadata(T3.self))
        
        #expect(tupleType.elementSize(at: 0) == 8)
        #expect(tupleType.elementSize(at: 1) == 16)
        #expect(tupleType.elementSize(at: 2) == 1)
        
        #expect(tupleType.elementOffset(at: 0) == 0)
        #expect(tupleType.elementOffset(at: 1) == 8)
        #expect(tupleType.elementOffset(at: 2) == 24)
        
        #expect(tupleType.elementOffset(at: 0, type: Metadata(T1.self)) == 0)
        #expect(tupleType.elementOffset(at: 1, type: Metadata(T2.self)) == 8)
        #expect(tupleType.elementOffset(at: 2, type: Metadata(T3.self)) == 24)
    }
}
