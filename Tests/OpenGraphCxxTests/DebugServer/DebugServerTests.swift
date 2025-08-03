//
//  DebugServerTests.swift
//  OpenGraphCxxTests

#if canImport(Darwin)
import Foundation
import OpenGraphCxx_Private.DebugServer
import Testing

@MainActor
struct DebugServerTests {
    private enum Command: String, CaseIterable, Hashable {
        case graphDescription = "graph/description"
        case profilerStart = "profiler/start"
        case profilerStop = "profiler/stop"
        case profilerReset = "profiler/reset"
        case profilerMark = "profiler/mark"
    }

    private func data(for command: Command) throws -> Data{
        let command = ["command": command.rawValue]
        return try JSONSerialization.data(withJSONObject: command)
    }

    @Test
    func commandTest() async throws {
        let debugServer = OG.DebugServer([.valid])
        let url = try #require(debugServer.copy_url()) as URL
        let components = try #require(URLComponents(url: url, resolvingAgainstBaseURL: false))
        let token = try #require(components.queryItems?.first { $0.name == "token" }?.value.flatMap { UInt32($0) })

        debugServer.run(3)
        let client = DebugClient()
        try await client.connect(to: url)

        for command in Command.allCases {
            if command == .graphDescription {
                continue
            }
            try await client.sendMessage(
                token: token,
                data: data(for: command)
            )
            let (_, responseData) = try await client.receiveMessage()
            let response = try #require(String(data: responseData, encoding: .utf8))
            #expect(response == command.rawValue)
        }
    }
}
#endif
