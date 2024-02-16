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
        let externalInt = External<Int>()
        XCTAssertEqual(externalInt.description, "External<Int>")
        #endif
        XCTAssertEqual(External<Int>.comparisonMode.rawValue, 3)
        XCTAssertEqual(External<Int>.flags.rawValue, 0)
    }
}
