//
//  AttributeTestBase.swift
//  OpenGraphCompatibilityTests

import Testing
import Foundation

/// Base class for Attribute Related test case
@available(*, deprecated, message: "Use GraphEnvironmentTrait instead")
class AttributeTestBase {
    private static let sharedGraph = Graph()
    private var graph: Graph
    private var subgraph: Subgraph
    
    init() {
        graph = Graph(shared: Self.sharedGraph)
        subgraph = Subgraph(graph: graph)
        Subgraph.current = subgraph
    }
    
    deinit {
        Subgraph.current = nil
    }
}

struct GraphEnvironmentTrait: TestTrait, TestScoping, SuiteTrait {
    private static let sharedGraph = Graph()
    private let semaphore = AsyncSemaphore(value: 1)


    @MainActor
    func provideScope(for test: Test, testCase: Test.Case?, performing function: @Sendable () async throws -> Void) async throws {
        await semaphore.wait()
        defer { semaphore.signal() }
        let graph = Graph(shared: Self.sharedGraph)
        let subgraph = Subgraph(graph: graph)
        let oldSubgraph = Subgraph.current

        Subgraph.current = subgraph
        try await function()
        Subgraph.current = oldSubgraph
    }

    var isRecursive: Bool {
        true
    }
}

extension Trait where Self == GraphEnvironmentTrait {
    static var graphScope: Self {
        GraphEnvironmentTrait()
    }
}
