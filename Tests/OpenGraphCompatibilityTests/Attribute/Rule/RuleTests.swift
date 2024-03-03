//
//  RuleTests.swift
//
//
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
