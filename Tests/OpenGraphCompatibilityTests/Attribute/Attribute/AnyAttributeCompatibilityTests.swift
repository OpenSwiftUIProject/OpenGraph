//
//  AnyAttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

// *** Program crashed: Bad pointer dereference at 0x0000000ffff9400a ***
// swift-testing framework will crash here on Linux
// Report to upstream for investigation when we bump to 5.10
#if canImport(Darwin)
//@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
@Suite(.disabled("Skip flaky CI tests after #154 temporary, See more info on #157"))
final class AnyAttributeCompatibilityTests: AttributeTestBase {
    @Test
    func constantValue() throws {
        let attributeNil = AnyAttribute.nil
        #expect(attributeNil.rawValue == 2)
    }

    // FIXME: Strange compile issue on non-ObjectiveC platform
    // Cannot look up associated type for imported conformance:
    // (struct_type decl=_OpenGraph.(file).AnyAttribute)
    // (associated_type_decl "_ObjectiveCType" access=public overridden=)
    // Please submit a bug report (https://swift.org/contributing/#reporting-bugs) and include the crash backtrace.
    #if canImport(ObjectiveC)
    @Test
    func description() throws {
        let attribute = AnyAttribute(rawValue: 0)
        #expect(attribute.description == "#0")
        
        let attributeNil = AnyAttribute.nil
        #expect(attributeNil.description == "#2")
    }
    
    @Test
    func current() {
        if compatibilityTestEnabled {
            // The value will not be nil if we run this test case seperately.
            // The value will be nil if we run the whole CompatibilityTests.
            // We need more knowledge to write the test case here.
            // #expect(AnyAttribute.current != nil)
        } else {
            #expect(AnyAttribute.current == nil)
        }
    }
    
    @Test
    func setFlags() throws {
        let attribute = AnyAttribute(Attribute(value: 0))
        #expect(attribute.flags == [])
        
        // Test mask = []
        attribute.flags = []
        
        attribute.setFlags([.active], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([.removable], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([.active, .invalidatable], mask: [])
        #expect(attribute.flags == [])
    
        // Test mask
        attribute.flags = []
        attribute.setFlags([.active], mask: [.active])
        #expect(attribute.flags == [.active])
        
        attribute.setFlags([.removable], mask: [.removable])
        #expect(attribute.flags == [.active, .removable])
        
        attribute.setFlags([.invalidatable], mask: [.active])
        #expect(attribute.flags == [.removable])
        
        attribute.setFlags([.active, .invalidatable], mask: [.active, .removable, .invalidatable])
        #expect(attribute.flags == [.active, .invalidatable])
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
                let attribute = AnyAttribute(Attribute(value: confirm))
                var visitor = Visitor()
                attribute.visitBody(&visitor)
            }
        }
    }
    #endif
}
#endif
