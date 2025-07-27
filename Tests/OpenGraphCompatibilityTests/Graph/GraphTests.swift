//
//  GraphTests.swift
//  OpenGraphCompatibilityTests

import Testing
import Foundation

struct GraphTests {
    @Test
    func graphCreate() throws {
        _ = Graph()
    }
    
    @Test
    func graphCreateShared() throws {
        let graph = Graph()
        _ = Graph(shared: graph)
        _ = Graph(shared: nil)
    }
    
    #if canImport(Darwin)
    @Test(.disabled(if: !compatibilityTestEnabled, "Not implemented on OG"))
    func graphArchiveJSON() throws {
        struct Graphs: Codable {
            var version: Int
            var graphs: [Graph]
            struct Graph: Codable {}
        }
        let name = "empty_graph.json"
        name.withCString { Graph.archiveJSON(name: $0) }
        let url = if #available(macOS 13.0, iOS 16.0, tvOS 16.0, watchOS 9.0, *) {
            URL(filePath: NSTemporaryDirectory().appending(name))
        } else {
            URL(fileURLWithPath: NSTemporaryDirectory().appending(name))
        }
        let data = try Data(contentsOf: url)
        let graphs = try JSONDecoder().decode(Graphs.self, from: data)
        #expect(graphs.version == 2)
    }
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Not implemented on OG"))
    func graphDescriptionDict() throws {
        let description = try #require(Graph.description(nil, options: ["format": "graph/dict"] as NSDictionary))
        let dic = description as! Dictionary<String, AnyHashable>
        #expect(dic["version"] as? UInt32 == 2)
        #expect((dic["graphs"] as? NSArray)?.count == 0)
    }
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Not implemented on OG"))
    func graphDescriptionDot() throws {
        let options = NSMutableDictionary()
        options["format"] = "graph/dot"
        #expect(Graph.description(nil, options: options) == nil)
        let graph = Graph()
        let description = try #require(Graph.description(graph, options: options))
        let dotGraph = description as! String
        let expectedEmptyDotGraph = #"""
        digraph {
        }
        
        """#
        #expect(dotGraph == expectedEmptyDotGraph)
    }
    
    @Test
    func graphCallback() {
        let graph = Graph()
        Graph.setUpdateCallback(graph, callback: nil)
        Graph.setUpdateCallback(graph) {
            print("Update")
        }
        Graph.setInvalidationCallback(graph, callback: nil)
        Graph.setInvalidationCallback(graph) { attr in
            print("Invalidate \(attr)")
        }
    }
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Not implemented on OG"))
    func counter() {
        let graph = Graph()
        #expect(graph.mainUpdates == 0)
    }
    #endif
}
