//
//  TupleTypeTests.swift
//  OpenGraphCompatibilityTests

import Testing

@Suite(.enabled(if: swiftToolchainSupported))
struct TupleTypeTests {
    class T1 {
        var a = 0
        var b: Double = 0
    }
    
    struct T2 {
        var a: Int = 0
        var b: Double = 0
    }
    
    enum T3 {
        case a, b
    }
    
    @Test
    func initType() {
        #expect(TupleType(T1.self).rawValue == Metadata(T1.self).rawValue)
        #expect(TupleType([T1.self, T2.self]).rawValue == Metadata((T1, T2).self).rawValue)
        #expect(TupleType([T1.self, T2.self, T3.self]).rawValue == Metadata((T1, T2, T3).self).rawValue)
    }
    
    
    @Test
    func type() {
        #expect(TupleType([T1.self, T2.self, T3.self]).type == (T1, T2, T3).self)
    }
    
    @Test(arguments:[
        (TupleType(Void.self), true, 0 ..< 0),
        (TupleType(T1.self), false, 0 ..< 1),
        (TupleType([T1.self, T2.self]), false, 0 ..< 2),
    ])
    func collectionAPI(tupleType: TupleType, expectedIsEmpty: Bool, expectedIndices: Range<Int>) {
        #expect(tupleType.isEmpty == expectedIsEmpty)
        #expect(tupleType.indices == expectedIndices)
    }
    
    @Test
    func elementTypeAndOffset() {
        let tupleType = TupleType([T1.self, T2.self, T3.self])
        #expect(tupleType.type(at: 0) == T1.self)
        #expect(tupleType.type(at: 1) == T2.self)
        #expect(tupleType.type(at: 2) == T3.self)
        
        #expect(tupleType.offset(at: 0, as: T1.self) == 0)
        #expect(tupleType.offset(at: 1, as: T2.self) == 8)
        #expect(tupleType.offset(at: 2, as: T3.self) == 24)
    }
    
    @Test
    func getAndSetElement() {
        let tupleType = TupleType([T1.self, T2.self])
        var tuple = (T1(), T2())
        #expect(tuple.0.a == 0)
        #expect(tuple.0.b == 0)
        #expect(tuple.1.a == 0)
        #expect(tuple.1.b == 0)
        
        var newT1 = T1()
        newT1.a = 1
        var newT2 = T2(a: 2)
        
        withUnsafeMutablePointer(to: &tuple) { tuplePointer in
            withUnsafePointer(to: newT1) {
                tupleType.setElement(in: tuplePointer, at: 0, from: $0, options: .assignCopy)
            }
            #expect(tuplePointer.pointee.0.a == 1)
            #expect(tuplePointer.pointee.1.a == 0)
            withUnsafePointer(to: newT2) {
                tupleType.setElement(in: tuplePointer, at: 1, from: $0, options: .assignCopy)
            }
            #expect(tuplePointer.pointee.0.a == 1)
            #expect(tuplePointer.pointee.1.a == 2)
        }
        
        tuple.0.a = 3
        tuple.1.a = 4
        
        withUnsafeMutablePointer(to: &tuple) { tuplePointer in
            withUnsafeMutablePointer(to: &newT1) {
                tupleType.getElement(in: tuplePointer, at: 0, to: $0, options: .assignCopy)
            }
            #expect(newT1.a == 3)
            #expect(newT2.a == 2)
            
            withUnsafeMutablePointer(to: &newT2) {
                tupleType.getElement(in: tuplePointer, at: 1, to: $0, options: .assignCopy)
            }
            #expect(newT2.a == 4)
        }
    }
}
