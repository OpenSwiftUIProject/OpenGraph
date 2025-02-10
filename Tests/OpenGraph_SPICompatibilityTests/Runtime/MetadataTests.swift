//
//  MetadataTests.swift
//  OpenGraph_SPICompatibilityTests

import Testing
import Numerics

@Suite(.enabled(if: swiftToolchainSupported))
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

    enum T4: Equatable {
        case none
        case empty
        case int(Int)
        case double(Double)
    }

    protocol P {
        var a: Int { get }
        var b: Double { get }
    }

    @Test
    func kind() {
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

    @Test
    func enumType() {
        var none = T4.none
        var empty = T4.empty
        var int = T4.int(1)
        var double = T4.double(2.0)
        let metadata = Metadata(T4.self)

        withUnsafePointer(to: none) { #expect(metadata.enumTag($0) == 2) }
        withUnsafePointer(to: empty) { #expect(metadata.enumTag($0) == 3) }
        withUnsafePointer(to: int) { #expect(metadata.enumTag($0) == 0) }
        withUnsafePointer(to: double) { #expect(metadata.enumTag($0) == 1) }

        withUnsafeMutablePointer(to: &int) {
            metadata.projectEnumData($0)
            #expect(UnsafeMutableRawPointer($0).assumingMemoryBound(to: Int.self).pointee == 1)
        }
        withUnsafeMutablePointer(to: &double) {
            metadata.projectEnumData($0)
            #expect(UnsafeMutableRawPointer($0).assumingMemoryBound(to: Double.self).pointee.isApproximatelyEqual(to: 2.0))
        }
        withUnsafeMutablePointer(to: &none) {
            #expect($0.pointee == .none)
            metadata.injectEnumTag(tag: 3, $0)
            #expect($0.pointee == .empty)
        }
        withUnsafeMutablePointer(to: &empty) {
            #expect($0.pointee == .empty)
            metadata.injectEnumTag(tag: 2, $0)
            #expect($0.pointee == .none)
        }
        withUnsafeMutablePointer(to: &int) {
            #expect($0.pointee == .int(1))

            metadata.injectEnumTag(tag: 1, $0)
            #expect(metadata.enumTag($0) == 1)
            #expect($0.pointee == .double(Double(bitPattern: 1)))

            metadata.injectEnumTag(tag: 2, $0)
            #expect($0.pointee == .none)

            metadata.injectEnumTag(tag: 3, $0)
            #expect($0.pointee == .empty)
        }
    }

    #if OPENGRAPH_SUPPORT_2024_API
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

    @Test
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

    @Test
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

extension Metadata {
    @_silgen_name("OGTypeGetEnumTag")
    static func getEnumTag<V>(_ value: V) -> UInt32
}
