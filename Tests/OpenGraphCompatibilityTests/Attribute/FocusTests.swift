//
//  FocusTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import XCTest

final class FocusTests: XCTestCase {
    struct Demo {
        var a: Int
        var b: Double
    }
    
    func testExample() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
//        let root = Attribute<Demo>(identifier: .nil)
        let type = Focus<Demo, Int>.self
        // FIXME: crash for some reason
//        let focus = type.init(root: root, keyPath: \.a)
//        XCTAssertEqual(focus.description, "• Focus<Demo, Int>")
//        XCTAssertEqual(focus.value, 0)
        XCTAssertEqual(type.flags.rawValue, 0)
        #endif
    }
}
