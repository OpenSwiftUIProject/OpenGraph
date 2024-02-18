//
//  ExternalTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import XCTest

final class ExternalTests: AttributeTestCase {
    func testExample() throws {
        let type = External<Int>.self
        #if OPENGRAPH_COMPATIBILITY_TEST
        let externalInt = type.init()
        XCTAssertEqual(externalInt.description, "External<Int>")
        #endif
        XCTAssertEqual(type.comparisonMode.rawValue, 3)
        XCTAssertEqual(type.flags.rawValue, 0)
    }
}
