//
//  OGAttributeTests.swift
//
//
//

import Testing

// *** Program crashed: Bad pointer dereference at 0x0000000ffff9400a ***
// swift-testing framework will crash here on Linux
// Report to upstream for investigation when we bump to 5.10
#if canImport(Darwin)
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
        
        attribute.setFlags([.removable], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([._1, .invalidatable], mask: [])
        #expect(attribute.flags == [])
    
        // Test mask
        attribute.flags = []
        attribute.setFlags([._1], mask: [._1])
        #expect(attribute.flags == [._1])
        
        attribute.setFlags([.removable], mask: [.removable])
        #expect(attribute.flags == [._1, .removable])
        
        attribute.setFlags([.invalidatable], mask: [._1])
        #expect(attribute.flags == [.removable])
        
        attribute.setFlags([._1, .invalidatable], mask: [._1, .removable, .invalidatable])
        #expect(attribute.flags == [._1, .invalidatable])
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
#endif
