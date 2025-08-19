//
//  GraphEnvironmentTrait.swift
//  OpenGraphTestsSupport

public import Testing

public struct GraphEnvironmentTrait: TestTrait, TestScoping, SuiteTrait {
    private static let sharedGraph = Graph()
    private static let semaphore = AsyncSemaphore(value: 1)

    @MainActor
    public func provideScope(for test: Test, testCase: Test.Case?, performing function: @Sendable () async throws -> Void) async throws {
        await Self.semaphore.wait()
        defer { Self.semaphore.signal() }
        let graph = Graph(shared: Self.sharedGraph)
        let subgraph = Subgraph(graph: graph)
        let oldSubgraph = Subgraph.current

        Subgraph.current = subgraph
        try await function()
        Subgraph.current = oldSubgraph
    }

    public var isRecursive: Bool {
        true
    }
}

extension Trait where Self == GraphEnvironmentTrait {
    public static var graphScope: Self {
        GraphEnvironmentTrait()
    }
}
