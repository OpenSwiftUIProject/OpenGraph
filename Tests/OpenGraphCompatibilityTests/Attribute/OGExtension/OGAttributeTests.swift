//
//  OGAttributeTests.swift
//
//
//  Created by Kyle on 2024/2/16.
//

import XCTest

final class OGAttributeTests: XCTestCase {
    func testNil() throws {
        let attributeNil = OGAttribute.nil
        XCTAssertEqual(attributeNil.rawValue, 2)
    }

    // FIXME: Strange compile issue on non-ObjectiveC platform
    // Cannot look up associated type for imported conformance:
    // (struct_type decl=_OpenGraph.(file).OGAttribute)
    // (associated_type_decl "_ObjectiveCType" access=public overridden=)
    // Please submit a bug report (https://swift.org/contributing/#reporting-bugs) and include the crash backtrace.
    #if canImport(ObjectiveC)
    func testDescription() throws {
        let attribute = OGAttribute(rawValue: 0)
        XCTAssertEqual(attribute.description, "#0")
        
        let attributeNil = OGAttribute.nil
        XCTAssertEqual(attributeNil.description, "#2")
    }
    
    func testCurrent() {
        #if OPENGRAPH_COMPATIBILITY_TEST
        // The value will not be nil if we run this test case seperately.
        // The value will be nil if we run the whole CompatibilityTests.
        // We need more knowledge to write the test case here.
        // XCTAssertNotNil(OGAttribute.current)
        #else
        XCTAssertNil(OGAttribute.current)
        #endif
    }
    
    // TODO: Add OGAttribute init
    func testSetFlags() throws {}
    #endif
}
