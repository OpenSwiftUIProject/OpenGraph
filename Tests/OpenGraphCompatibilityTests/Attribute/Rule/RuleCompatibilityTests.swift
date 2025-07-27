//
//  RuleCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct RuleCompatibilityTests {
    @Test
    func ruleInitialValue() throws {
        struct A: Rule {
            typealias Value = Int
            var value: Int
        }
        #expect(A.initialValue == nil)
    }
}
