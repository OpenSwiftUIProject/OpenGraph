//
//  Scaffolding.swift
//
//
//  Created by Kyle on 2024/2/18.
//

import Testing
import XCTest

final class AllTests: XCTestCase {
    func testAll() async {
        await XCTestScaffold.runAllTests(hostedBy: self)
    }
}
struct PointerOffsetTests {
    struct Tuple<A, B> {
        var first: A
        var second: B
    }
    struct Triple<A, B, C> {
        var first: A
        var second: B
        var third: C
    }
    

    
}
