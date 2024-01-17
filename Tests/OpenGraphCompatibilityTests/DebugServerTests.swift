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
@_silgen_name("AGDebugServerStart")
@inline(__always)
private func debugServerStart(_ port: UInt) -> UnsafeRawPointer?
@_silgen_name("AGDebugServerCopyURL")
@inline(__always)
private func debugServerCopyURL() -> CFURL?
#else
import OpenGraph
import _OpenGraph
@_silgen_name("OGDebugServerStart")
@inline(__always)
private func debugServerStart(_ port: UInt) -> UnsafeRawPointer?
@_silgen_name("OGDebugServerCopyURL")
@inline(__always)
private func debugServerCopyURL() -> CFURL?
#endif

final class DebugServerTests: XCTestCase {
    func testExample() throws {
        XCTAssertNil(debugServerStart(2))
        XCTAssertNil(debugServerCopyURL())
        #if OPENGRAPH_COMPATIBILITY_TEST
        // To make AG start debugServer, we need to pass internal_diagnostics check.
        // In debug mode, we can breakpoint on `_ZN2AG11DebugServerC2Ej` and
        // executable `reg write w0 1` after `internal_diagnostics` call.
        throw XCTSkip("Skip on AG due to internal_diagnostics")
        #else
        _ = try XCTUnwrap(debugServerStart(10089))
        
        let url = try XCTUnwrap(debugServerCopyURL())
        let urlString = (url as URL).absoluteString
        XCTAssertTrue(urlString.hasPrefix("graph://"))
        #endif
    }
}
#endif
