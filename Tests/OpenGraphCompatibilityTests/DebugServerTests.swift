//
//  DebugServerTests.swift
//  
//
//  Created by Kyle on 2024/1/15.
//

#if canImport(Darwin)
import XCTest
import Foundation
import CoreFoundation

#if OPENGRAPH_COMPATIBILITY_TEST
import AttributeGraph
#else
import OpenGraph
#endif

final class DebugServerTests: XCTestCase {
    func testExample() throws {
        XCTAssertNil(debugServerStart(0))
        XCTAssertNil(debugServerCopyURL())
        #if OPENGRAPH_COMPATIBILITY_TEST
        // To make AG start debugServer, we need to pass internal_diagnostics check.
        // In debug mode, we can breakpoint on `_ZN2AG11DebugServer5startEj` and
        // executable `reg write w0 1` after `internal_diagnostics` call.
        throw XCTSkip("Skip on AG due to internal_diagnostics check")
        #else
        _ = try XCTUnwrap(debugServerStart(1))
        let url = try XCTUnwrap(debugServerCopyURL())
        let urlString = (url as URL).absoluteString
        XCTAssertTrue(urlString.hasPrefix("graph://"))
        debugServerRun(1)
        #endif
    }
}
#endif
