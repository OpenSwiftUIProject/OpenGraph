//
//  DebugServerTests.swift
//
//
//  Created by Kyle on 2024/1/15.
//

#if canImport(Darwin)
import CoreFoundation
import Foundation
import OpenGraphShims
import XCTest

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
