//
//  AttributeTests.swift
//  
//
//  Created by Kyle on 2024/2/17.
//

import XCTest

final class AttributeTests: AttributeTestCase {

    func testInitWithValue() throws {
        let intAttribute = Attribute(value: 0)
        XCTAssertEqual(intAttribute.value, 0)
    }
}
