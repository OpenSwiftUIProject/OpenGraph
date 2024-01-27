//
//  TupleTypeTests.swift
//  
//
//  Created by Kyle on 2024/1/27.
//

import XCTest

final class TupleTypeTests: XCTestCase {
    override func setUp() async throws {
        #if !OPENGRAPH_COMPATIBILITY_TEST
        throw XCTSkip("OGTupleType is not implemented")
        #endif
    }
    
    func testExample() throws {
        let value = (3, 5.0)
        let tupleType = OGTupleType(type(of: value))
        XCTAssertEqual(tupleType.count, 2)
        XCTAssertEqual(tupleType.size, 16)
        XCTAssertTrue(tupleType.type(at: 0) == Int.self)
        XCTAssertTrue(tupleType.type(at: 1) == Double.self)
    }
}
