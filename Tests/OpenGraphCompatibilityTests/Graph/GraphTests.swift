//
//  GraphTests.swift
//
//
//

import Testing
import Foundation

struct GraphTests {
    @Test
    func graphCreate() throws {
        _ = OGGraph()
    }
    
    @Test
    func graphCreateShared() throws {
        let graph = OGGraph()
        _ = OGGraph(shared: graph)
        _ = OGGraph(shared: nil)
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
        name.withCString { OGGraph.archiveJSON(name: $0) }
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
        let description = try #require(OGGraph.description(nil, options: ["format": "graph/dict"] as NSDictionary))
        let dic = description.takeUnretainedValue() as! Dictionary<String, AnyHashable>
        #expect(dic["version"] as? UInt32 == 2)
        #expect((dic["graphs"] as? NSArray)?.count == 0)
    }
    
    @Test(.disabled(if: !compatibilityTestEnabled, "Not implemented on OG"))
    func graphDescriptionDot() throws {
        let options = NSMutableDictionary()
        options["format"] = "graph/dot"
        #expect(OGGraph.description(nil, options: options) == nil)
        let graph = OGGraph()
        let description = try #require(OGGraph.description(graph, options: options))
        let dotGraph = description.takeUnretainedValue() as! String
        let expectedEmptyDotGraph = #"""
        digraph {
        }
        
        """#
        #expect(dotGraph == expectedEmptyDotGraph)
    }
    #endif
    
    @Test
    func graphCallback() {
        let graph = OGGraph()
        OGGraph.setUpdateCallback(graph: graph, callback: nil)
        OGGraph.setUpdateCallback(graph: graph) {
            print("Update")
        }
        OGGraph.setInvalidationCallback(graph: graph, callback: nil)
        OGGraph.setInvalidationCallback(graph: graph) { attr in
            print("Invalidate \(attr)")
        }
    }
}
