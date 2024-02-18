//
//  TypeKindTests.swift
//
//
//  Created by Kyle on 2024/1/8.
//

import Testing

private protocol P {}

@Suite(.disabled(if: !compatibilityTestEnabled, "OGTypeID.kind is not implemented"))
struct TypeKindTests {
    class T1 {}
    struct T2 {}
    enum T3 {}
    
    @Test
    func kindCases() throws {
        #expect(OGTypeID(T1.self).kind == .class)
        #expect(OGTypeID(T2.self).kind == .struct)
        #expect(OGTypeID(T3.self).kind == .enum)
        
        #expect(OGTypeID(Void?.self).kind == .optional)
        #expect(OGTypeID(Int?.self).kind == .optional)
        #expect(OGTypeID(T1?.self).kind == .optional)
        #expect(OGTypeID((T1, T2)?.self).kind == .optional)

        #expect(OGTypeID(Void.self).kind == .tuple)
        #expect(OGTypeID((Int, Double?).self).kind == .tuple)
        #expect(OGTypeID((T1, T2, T3).self).kind == .tuple)
        
        #expect(OGTypeID((() -> Void).self).kind == .function)
        
        #expect(OGTypeID(P.self).kind == .existential)
        #expect(OGTypeID((any P).self).kind == .existential)
        
        #expect(OGTypeID(P.Protocol.self).kind == .metatype)
        #expect(OGTypeID(type(of: Int.self)).kind == .metatype)
    }
}
