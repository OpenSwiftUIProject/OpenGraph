//
//  DebugServerTests.swift
//  OpenGraphCxxTests

#if canImport(Darwin)
import Foundation
import OpenGraphCxx_Private.DebugServer
import Testing

@MainActor
struct DebugServerTests {
    typealias Command = DebugClient.Command

    private func data(for command: Command) throws -> Data{
        let command = ["command": command.rawValue]
        return try JSONSerialization.data(withJSONObject: command)
    }

    @Test
    func commandTest() async throws {
        var debugServer = OG.DebugServer([.valid])
        let cfURL = debugServer.copy_url()
        let url = try #require(cfURL) as URL
        let components = try #require(URLComponents(url: url, resolvingAgainstBaseURL: false))
        let token = try #require(components.queryItems?.first { $0.name == "token" }?.value.flatMap { UInt32($0) })
        debugServer.run(1)
        let client = DebugClient()
        let updates = client.connect(to: url)
        try await confirmation { confirm in
            for try await update in updates {
                switch update {
                case .ready:
                    confirm()
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
                    debugServer.shutdown() // TODO: The shutdown should close the connection, but it does not for OGDebugServer currently.
                    client.disconnect()
                default:
                    break
                }
            }
        }
    }
}
#endif
