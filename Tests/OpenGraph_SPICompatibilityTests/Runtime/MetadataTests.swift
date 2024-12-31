//
//  MetadataTests.swift
//  OpenGraph_SPICompatibilityTests

import Testing

struct MetadataTests {
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
    
    protocol P {
        var a: Int { get }
        var b: Double { get }
    }
    
    @Test(.enabled(if: swiftToolchainSupported))
    func kind() throws {
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
    
    #if OPENGRAPH_SUPPORT_2024_API
    @Test(.enabled(if: swiftToolchainSupported))
    func descriptor() {
        let t1 = Metadata(T1.self).descriptor
        let t2 = Metadata(T2.self).descriptor
        let t3 = Metadata(T3.self).descriptor
        let p = Metadata(P.self).descriptor
        let optionalP = Metadata(P?.self).descriptor

        #expect(t1 != nil)
        #expect(t2 != nil)
        #expect(t3 != nil)

        #expect(p == nil)
        #expect(optionalP != nil)
        
        #expect(t1 == Metadata(T1.self).descriptor)
    }
    #endif
    
    @Test(.enabled(if: swiftToolchainSupported))
    func nominalDescriptor() {
        let t1 = Metadata(T1.self).nominalDescriptor
        let t2 = Metadata(T2.self).nominalDescriptor
        let t3 = Metadata(T3.self).nominalDescriptor
        let p = Metadata(P.self).nominalDescriptor
        let optionalP = Metadata(P?.self).nominalDescriptor

        #expect(t1 == nil)
        #expect(t2 != nil)
        #expect(t3 != nil)
        #expect(p == nil)
        #expect(optionalP != nil)
    }
    
    @Test(.enabled(if: swiftToolchainSupported))
    func nominalDescriptorName() throws {
        let t1 = Metadata(T1.self).nominalDescriptorName
        let t2 = Metadata(T2.self).nominalDescriptorName
        let t3 = Metadata(T3.self).nominalDescriptorName
        let p = Metadata(P.self).nominalDescriptorName
        let optionalP = Metadata(P?.self).nominalDescriptorName
        
        #expect(t1 == nil)
        try #expect(String(cString: #require(t2)) == "T2")
        try #expect(String(cString: #require(t3)) == "T3")
        #expect(p == nil)
        try #expect(String(cString: #require(optionalP)) == "Optional")
    }
}
