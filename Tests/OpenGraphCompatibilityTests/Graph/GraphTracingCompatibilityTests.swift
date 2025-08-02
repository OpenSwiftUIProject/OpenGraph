//
//  GraphTracingCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct GraphTracingCompatibilityTests {
    @Test
    func tracing() {
        let graph = Graph()
        Graph.startTracing(graph, flags: [])
        Graph.stopTracing(graph)
    }

    @Test
    func tracingAll() {
        Graph.startTracing(nil, flags: [])
        Graph.stopTracing(nil)
    }

    @Test
    func options() {
        let option = Graph.TraceFlags(rawValue: 1)
        #expect(option == .enabled)
    }
}
