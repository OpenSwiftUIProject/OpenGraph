//
//  OGAttributeTests.swift
//
//
//  Created by Kyle on 2024/2/16.
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
final class OGAttributeTests: AttributeTestBase {
    @Test
    func constantValue() throws {
        let attributeNil = OGAttribute.nil
        #expect(attributeNil.rawValue == 2)
    }

    // FIXME: Strange compile issue on non-ObjectiveC platform
    // Cannot look up associated type for imported conformance:
    // (struct_type decl=_OpenGraph.(file).OGAttribute)
    // (associated_type_decl "_ObjectiveCType" access=public overridden=)
    // Please submit a bug report (https://swift.org/contributing/#reporting-bugs) and include the crash backtrace.
    #if canImport(ObjectiveC)
    @Test
    func description() throws {
        let attribute = OGAttribute(rawValue: 0)
        #expect(attribute.description == "#0")
        
        let attributeNil = OGAttribute.nil
        #expect(attributeNil.description == "#2")
    }
    
    @Test
    func current() {
        if compatibilityTestEnabled {
            // The value will not be nil if we run this test case seperately.
            // The value will be nil if we run the whole CompatibilityTests.
            // We need more knowledge to write the test case here.
            // #expect(OGAttribute.current != nil)
        } else {
            #expect(OGAttribute.current == nil)
        }
    }
    
    @Test
    func setFlags() throws {
        let attribute = OGAttribute(Attribute(value: 0))
        #expect(attribute.flags == [])
        
        // Test mask = []
        attribute.flags = []
        
        attribute.setFlags([._1], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([._2], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([._1, ._4], mask: [])
        #expect(attribute.flags == [])
    
        // Test mask
        attribute.flags = []
        attribute.setFlags([._1], mask: [._1])
        #expect(attribute.flags == [._1])
        
        attribute.setFlags([._2], mask: [._2])
        #expect(attribute.flags == [._1, ._2])
        
        attribute.setFlags([._4], mask: [._1])
        #expect(attribute.flags == [._2])
        
        attribute.setFlags([._1, ._4], mask: [._1, ._2, ._4])
        #expect(attribute.flags == [._1, ._4])
    }
    
    @Test
    func visitBody() async {
        struct Visitor: AttributeBodyVisitor {
            func visit<Body>(body: UnsafePointer<Body>) where Body : _AttributeBody {
                guard let confirm = body.pointee as? Confirmation else {
                    Issue.record()
                    return
                }
                confirm()
            }
        }
        
        await withKnownIssue("Fetch Confirmation value from the body pointer") {
            await confirmation("Visit Body", expectedCount: 1) { confirm in
                let attribute = OGAttribute(Attribute(value: confirm))
                var visitor = Visitor()
                attribute.visitBody(&visitor)
            }
        }
    }
    #endif
}
