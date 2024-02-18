//
//  ExternalTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import Testing

final class ExternalTests: AttributeTestBase {
    @Test
    func example() throws {
        let type = External<Int>.self
        if compatibilityTestEnabled {
            let externalInt = type.init()
            #expect(externalInt.description == "External<Int>")
        }
        #expect(type.comparisonMode == ._3)
        #expect(type.flags == [])
        
    }
}
