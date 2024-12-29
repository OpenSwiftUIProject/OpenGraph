//
//  TypeKindTests.swift
//
//
//

import Testing

private protocol P {}

@Suite(.disabled(if: !compatibilityTestEnabled, "Metadata.kind is not implemented"))
struct TypeKindTests {
    class T1 {}
    struct T2 {}
    enum T3 {}
    
    @Test
    func kindCases() throws {
        #expect(Metadata(T1.self).kind == .class)
        #expect(Metadata(T2.self).kind == .struct)
        #expect(Metadata(T3.self).kind == .enum)
        
        #expect(Metadata(Void?.self).kind == .optional)
        #expect(Metadata(Int?.self).kind == .optional)
        #expect(Metadata(T1?.self).kind == .optional)
        #expect(Metadata((T1, T2)?.self).kind == .optional)

        #expect(Metadata(Void.self).kind == .tuple)
        #expect(Metadata((Int, Double?).self).kind == .tuple)
        #expect(Metadata((T1, T2, T3).self).kind == .tuple)
        
        #expect(Metadata((() -> Void).self).kind == .function)
        
        #expect(Metadata(P.self).kind == .existential)
        #expect(Metadata((any P).self).kind == .existential)
        
        #expect(Metadata(P.Protocol.self).kind == .metatype)
        #expect(Metadata(type(of: Int.self)).kind == .metatype)
    }
}
