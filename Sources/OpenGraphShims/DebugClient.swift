//
//  DebugServerTests.swift
//  OpenGraphShims

#if canImport(Darwin)
public import Foundation
public import Network

#if canImport(OpenGraphCxx_Private)
public import OpenGraphCxx_Private.DebugServer
#endif

public struct ConnectionUpdates: AsyncSequence {
    public typealias Element = NWConnection.State
    
    private let stream: AsyncStream<NWConnection.State>
    
    fileprivate init(stream: AsyncStream<NWConnection.State>) {
        self.stream = stream
    }
    
    public func makeAsyncIterator() -> AsyncStream<NWConnection.State>.AsyncIterator {
        stream.makeAsyncIterator()
    }
}

@_spi(Debug)
public final class DebugClient {
    private var connection: NWConnection?
    private let queue = DispatchQueue(label: "org.openswiftuiproject.opengraph.debugclient")

    public func connect(to url: URL) -> ConnectionUpdates {
        guard let host = url.host, let port = url.port else {
            return ConnectionUpdates(stream: AsyncStream { continuation in
                continuation.yield(.failed(NWError.posix(.EINVAL)))
                continuation.finish()
            })
        }
        let nwHost = NWEndpoint.Host(host)
        let nwPort = NWEndpoint.Port(integerLiteral: UInt16(port))
        connection = NWConnection(host: nwHost, port: nwPort, using: .tcp)
        let stream = AsyncStream<NWConnection.State> { continuation in
            connection?.stateUpdateHandler = { state in
                continuation.yield(state)
                if case .cancelled = state {
                    continuation.finish()
                }
            }
            connection?.start(queue: queue)
        }
        return ConnectionUpdates(stream: stream)
    }

    public func sendMessage(token: UInt32, data: Data) async throws {
        guard let connection else {
            throw ClientError.notConnected
        }
        let header = DebugServerMessageHeader(
            token: token,
            unknown: 0,
            length: numericCast(data.count),
            unknown2: 0
        )
        let headerData = withUnsafePointer(to: header) {
            Data(bytes: UnsafeRawPointer($0), count: MemoryLayout<DebugServerMessageHeader>.size)
        }
        try await send(data: headerData, on: connection)
        guard header.length > 0 else {
            return
        }
        try await send(data: data, on: connection)
    }

    public func receiveMessage() async throws -> (header: DebugServerMessageHeader, data: Data) {
        guard let connection = connection else {
            throw ClientError.notConnected
        }
        let headerData = try await receive(
            length: MemoryLayout<DebugServerMessageHeader>.size,
            from: connection
        )
        let header = headerData.withUnsafeBytes { bytes in
            let buffer = bytes.bindMemory(to: UInt32.self)
            return DebugServerMessageHeader(
                token: buffer[0],
                unknown: buffer[1],
                length: buffer[2],
                unknown2: buffer[3]
            )
        }
        guard header.length > 0 else {
            return (header: header, data: Data())
        }
        let payloadData = try await receive(
            length: numericCast(header.length),
            from: connection
        )
        return (header: header, data: payloadData)
    }

    public func disconnect() {
        connection?.cancel()
        connection = nil
    }

    private func send(data: Data, on connection: NWConnection) async throws {
        return try await withCheckedThrowingContinuation { continuation in
            connection.send(content: data, completion: .contentProcessed { error in
                if let error {
                    continuation.resume(throwing: error)
                } else {
                    continuation.resume()
                }
            })
        }
    }

    private func receive(length: Int, from connection: NWConnection) async throws -> Data {
        return try await withCheckedThrowingContinuation { continuation in
            connection.receive(minimumIncompleteLength: length, maximumLength: length) { data, _, isComplete, error in
                if let error {
                    continuation.resume(throwing: error)
                } else if let data {
                    continuation.resume(returning: data)
                } else {
                    continuation.resume(throwing: ClientError.noDataReceived)
                }
            }
        }
    }
}

enum ClientError: Error {
    case invalidURL
    case notConnected
    case connectionCancelled
    case noDataReceived
}

#endif
