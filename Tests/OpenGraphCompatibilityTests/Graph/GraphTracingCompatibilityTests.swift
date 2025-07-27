//
//  GraphTracingCompatibilityTests.swift
//  OpenGraphCompatibilityTests

import Testing

struct GraphTracingCompatibilityTests {
    @Test
    func tracing() {
        let graph = Graph()
        Graph.startTracing(graph, options: [])
        Graph.stopTracing(graph)
    }

    @Test
    func tracingAll() {
        Graph.startTracing(nil, options: [])
        Graph.stopTracing(nil)
    }

    @Test
    func options() {
        let option = Graph.TraceFlags(rawValue: 1)
        #expect(option == ._1)
    }
}
