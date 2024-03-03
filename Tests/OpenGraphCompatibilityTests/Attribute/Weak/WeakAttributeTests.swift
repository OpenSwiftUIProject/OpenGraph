//
//  WeakAttributeTests.swift
//  
//
//  Created by Kyle on 2024/3/3.
//

import Testing

final class WeakAttributeTests: AttributeTestBase {
    @Test
    func initTest() {
        let _ = WeakAttribute<Int>()
        let _ = WeakAttribute<Int>(nil)
        let attr = Attribute(value: 0)
        let _ = WeakAttribute(attr)
    }
}
