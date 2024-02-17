//
//  GraphTests.swift
//
//
//  Created by Kyle on 2024/1/18.
//

import XCTest

final class GraphTests: XCTestCase {
    func testGraphCreate() throws {
        _ = OGGraph()
    }
    
    func testGraphCreateShared() throws {
        let graph = OGGraph()
        _ = OGGraph(shared: graph)
        _ = OGGraph(shared: nil)
    }
    
    func testGraphArchiveJSON() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
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
        XCTAssertEqual(graphs.version, 2)
        #else
        throw XCTSkip("Not implemented on OG")
        #endif
    }
    
    func testGraphDescriptionDict() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
        let description = try XCTUnwrap(OGGraph.description(nil, options: ["format": "graph/dict"] as NSDictionary))
        let dic = description.takeUnretainedValue() as! Dictionary<String, AnyHashable>
        XCTAssertEqual(dic["version"] as? UInt32, 2)
        XCTAssertEqual((dic["graphs"] as? NSArray)?.count, 0)
        #else
        throw XCTSkip("Not implemented on OG")
        #endif
    }
    
    func testGraphDescriptionDot() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
        let options = NSMutableDictionary()
        options["format"] = "graph/dot"
        XCTAssertNil(OGGraph.description(nil, options: options))
        let graph = OGGraph()
        let description = try XCTUnwrap(OGGraph.description(graph, options: options))
        let dotGraph = description.takeUnretainedValue() as! String
        let expectedEmptyDotGraph = #"""
        digraph {
        }
        
        """#
        XCTAssertEqual(dotGraph, expectedEmptyDotGraph)
        #else
        throw XCTSkip("Not implemented on OG")
        #endif
    }
}
