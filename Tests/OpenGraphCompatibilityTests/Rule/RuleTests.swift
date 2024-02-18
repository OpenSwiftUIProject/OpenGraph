//
//  RuleTests.swift
//
//
//  Created by Kyle on 2023/10/17.
//

import Testing

struct RuleTests {
    @Test
    func ruleInitialValue() throws {
        struct A: Rule {
            typealias Value = Int
            var value: Int
        }
        #expect(A.initialValue == nil)
    }
}
