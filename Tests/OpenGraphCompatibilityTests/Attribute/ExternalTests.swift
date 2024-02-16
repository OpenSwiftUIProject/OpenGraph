//
//  ExternalTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import XCTest

final class ExternalTests: XCTestCase {
    func testExample() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
        let type = External<Int>.self
        let externalInt = type.init()
        XCTAssertEqual(externalInt.description, "External<Int>")
        #endif
        XCTAssertEqual(type.comparisonMode.rawValue, 3)
        XCTAssertEqual(type.flags.rawValue, 0)
    }
}
