//
//  OGTypeIDDebugTests.swift
//  OpenGraphTests

@_spi(Debug) import OpenGraphShims
import Testing

@Suite(.disabled(if: !attributeGraphEnabled, "forEachField is not implemented for OG"))
struct OGTypeIDDebugTests {
    struct Demo1 {
        var a: Int = .zero
        var b: Double = .zero
    }

    class Demo2 {
        var a: Int = .zero
        var b: Double = .zero
    }
    
    @Test
    func layout() {
        #expect(OGTypeID(Demo1.self).layoutDescription == #"""
        struct Demo1 {
        \#tvar a: Int // offset = 0x0
        \#tvar b: Double // offset = 0x8
        }
        
        """#)
        
        #expect(OGTypeID(Demo2.self).layoutDescription == #"""
        class Demo2 {
        \#tvar a: Int // offset = 0x10
        \#tvar b: Double // offset = 0x18
        }
        
        """#)
    }
    
}
