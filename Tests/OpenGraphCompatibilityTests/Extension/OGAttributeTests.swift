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
    
    func testDescription() throws {
        let attribute = OGAttribute(rawValue: 0)
        XCTAssertEqual(attribute.description, "#0")
        
        let attributeNil = OGAttribute.nil
        XCTAssertEqual(attributeNil.description, "#2")
    }
}
