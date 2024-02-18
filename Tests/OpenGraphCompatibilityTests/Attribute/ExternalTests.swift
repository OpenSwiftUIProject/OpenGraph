//
//  ExternalTests.swift
//  
//
//  Created by Kyle on 2024/2/16.
//

import Testing

// *** Program crashed: Bad pointer dereference at 0x0000000ffff9400a ***
// swift-testing framework will crash here on Linux
// Report to upstream for investigation when we bump to 5.10
#if canImport(Darwin)
@Suite(.disabled(if: !compatibilityTestEnabled, "Attribute is not implemented"))
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
#endif
