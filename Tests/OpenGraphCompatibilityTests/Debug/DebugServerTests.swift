//
//  DebugServerTests.swift
//
//
//  Created by Kyle on 2024/1/15.
//

#if canImport(Darwin)
import CoreFoundation
import Foundation
import XCTest

final class DebugServerTests: XCTestCase {
    func testServer() throws {
        XCTAssertNil(OGDebugServer.start(mode: 0))
        XCTAssertNil(OGDebugServer.copyURL())
        #if OPENGRAPH_COMPATIBILITY_TEST
        // To make AG start debugServer, we need to pass internal_diagnostics check.
        // In debug mode, we can breakpoint on `_ZN2AG11DebugServer5startEj` and
        // executable `reg write w0 1` after `internal_diagnostics` call.
        // Or we can disable SIP on the target darwinOS and run `sudo sysctl kern.osvariant_status=xx` to workaround
        throw XCTSkip("Skip on AG due to internal_diagnostics check")
        #else
        _ = try XCTUnwrap(OGDebugServer.start(mode: 1))
        let url = try XCTUnwrap(OGDebugServer.copyURL())
        let urlString = (url.takeRetainedValue() as URL).absoluteString
        XCTAssertTrue(urlString.hasPrefix("graph://"))
        OGDebugServer.run(timeout: 1)
        #endif
    }
}
#endif
