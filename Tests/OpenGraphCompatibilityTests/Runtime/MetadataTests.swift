//
//  MetadataTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct MetadataTests {
    @Test(.enabled(if: swiftToolchainSupported))
    func kindCases() throws {
        class T1 {}
        struct T2 {}
        enum T3 {}
        protocol P {}
        
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
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Metadata is not implemented"))
    func descriptor() throws {
        let n1 = try #require(Metadata(Int.self).nominalDescriptor)
        let n2 = try #require(Metadata(String.self).nominalDescriptor)
        let n3 = try #require(Metadata(Int.self).nominalDescriptor)
        
        #expect(n1 != n2)
        #expect(n1 == n3)
    }
    
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
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Metadata is not implemented"))
    func description() {
        #expect(Metadata(T1.self).description == "MetadataTests.T1")
        #expect(Metadata(T2.self).description == "MetadataTests.T2")
        #expect(Metadata(T3.self).description == "MetadataTests.T3")
    }
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Metadata is not implemented"))
    func forEachField() throws {
        for options in [OGTypeApplyOptions._1] {
            let result = Metadata(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 24 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == true)
        }
        for options in [OGTypeApplyOptions._2, ._4, []] {
            let result = Metadata(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 24 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == false)
        }
        for options in [OGTypeApplyOptions._2, []] {
            let result = Metadata(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    #expect(type is Int.Type)
                    return true
                } else if offset == 8 {
                    #expect(type is Double.Type)
                    return true
                } else {
                    return false
                }
            }
            #expect(result == true)
        }
        for options in [OGTypeApplyOptions._1, ._4] {
            let result = Metadata(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 8 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == false)
        }
        for options in [OGTypeApplyOptions._1, ._2, ._4, []] {
            let result = Metadata(T3.self).forEachField(options: options) { _, _, _ in
                true
            }
            #expect(result == false)
        }
    }
}