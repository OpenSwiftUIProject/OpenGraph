//
//  AnyAttributeCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

// *** Program crashed: Bad pointer dereference at 0x0000000ffff9400a ***
// swift-testing framework will crash here on Linux
// Report to upstream for investigation when we bump to 5.10
#if canImport(Darwin)
//@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"), .graphScope)
@Suite(.disabled("Skip flaky CI tests after #154 temporary, See more info on #157"), .graphScope)
struct AnyAttributeCompatibilityTests {
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
        typealias Flags = AnyAttribute.Flags

        let attribute = AnyAttribute(Attribute(value: 0))
        #expect(attribute.flags == [])
        
        // Test mask = []
        attribute.flags = []
        
        attribute.setFlags([Flags(rawValue: 1)], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([Flags(rawValue: 2)], mask: [])
        #expect(attribute.flags == [])
        
        attribute.setFlags([Flags(rawValue: 1), Flags(rawValue: 4)], mask: [])
        #expect(attribute.flags == [])
    
        // Test mask
        attribute.flags = []
        attribute.setFlags([Flags(rawValue: 1)], mask: [Flags(rawValue: 1)])
        #expect(attribute.flags == [Flags(rawValue: 1)])
        
        attribute.setFlags([Flags(rawValue: 2)], mask: [Flags(rawValue: 2)])
        #expect(attribute.flags == [Flags(rawValue: 1), Flags(rawValue: 2)])
        
        attribute.setFlags([Flags(rawValue: 4)], mask: [Flags(rawValue: 1)])
        #expect(attribute.flags == [Flags(rawValue: 2)])
        
        attribute.setFlags([Flags(rawValue: 1), Flags(rawValue: 4)], mask: [Flags(rawValue: 1), Flags(rawValue: 2), Flags(rawValue: 4)])
        #expect(attribute.flags == [Flags(rawValue: 1), Flags(rawValue: 4)])
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
