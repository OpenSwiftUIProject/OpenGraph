//
//  TypeIDTests.swift
//
//
//  Created by Kyle on 2024/1/24.
//

import OpenGraphShims
import XCTest

final class TypeIDTests: XCTestCase {
    func testExample() throws {
        let i = OGTypeID(Int.self)
        let result = i.forEachField(options: []) { _, _, _ in
            false
        }
        XCTAssertFalse(result)
    }
}
