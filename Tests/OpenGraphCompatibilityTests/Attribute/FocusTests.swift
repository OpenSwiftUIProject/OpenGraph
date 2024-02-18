//
//  FocusTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
final class FocusTests: AttributeTestBase {
    struct Demo {
        var a: Int
        var b: Double
    }
    
    @Test
    func example() throws {
//        let root = Attribute<Demo>(identifier: .nil)
        let type = Focus<Demo, Int>.self
        // FIXME: crash for some reason
//        let focus = type.init(root: root, keyPath: \.a)
//        XCTAssertEqual(focus.description, "• Focus<Demo, Int>")
//        XCTAssertEqual(focus.value, 0)
        #expect(type.flags == [])
    }
}
