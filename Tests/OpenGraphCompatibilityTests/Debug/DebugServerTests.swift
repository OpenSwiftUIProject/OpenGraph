//
//  DebugServerTests.swift
//  OpenGraphCompatibilityTests

#if canImport(Darwin)
import CoreFoundation
import Foundation
import Testing

@MainActor
struct DebugServerTests {
    @Test
    func testMode0() {
        #expect(OGDebugServer.start(mode: 0) == nil)
        #expect(OGDebugServer.copyURL() == nil)
    }

    // To make AG start debugServer, we need to pass internal_diagnostics check.
    // In debug mode, we can breakpoint on `_ZN2AG11DebugServer5startEj` and
    // executable `reg write w0 1` after `internal_diagnostics` call.
    // Or we can disable SIP on the target darwinOS and run `sudo sysctl kern.osvariant_status=xx` to workaround
    @Test(
        .disabled(if: compatibilityTestEnabled, "Skip on AG due to internal_diagnostics check"),
    )
    func testMode1() throws {
        let _ = try #require(OGDebugServer.start(mode: 1))
        let url = try #require(OGDebugServer.copyURL())
        let urlString = (url as URL).absoluteString
        #expect(urlString.hasPrefix("graph://"))
        OGDebugServer.run(timeout: 1)
        OGDebugServer.stop()
    }
}
#endif
