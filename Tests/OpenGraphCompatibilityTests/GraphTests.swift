//
//  GraphTests.swift
//
//
//  Created by Kyle on 2024/1/18.
//

import XCTest

final class GraphTests: XCTestCase {
    func testGraphCreate() throws {
        _ = graphCreate()
    }
    
    func testGraphCreateShared() throws {
        let graph = graphCreate()
        _ = graphCreateShared(graph)
        _ = graphCreateShared(nil)
    }
    
    func testGraphArchiveJSON() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
        struct Graphs: Codable {
            var version: Int
            var graphs: [Graph]
            struct Graph: Codable {}
        }
        let name = "empty_graph.json"
        name.withCString { graphArchiveJSON($0) }
        let url = URL(filePath: NSTemporaryDirectory().appending(name))
        let data = try Data(contentsOf: url)
        let graphs = try JSONDecoder().decode(Graphs.self, from: data)
        XCTAssertEqual(graphs.version, 2)
        #else
        throw XCTSkip("Not implemented on OG")
        #endif
    }
    
    func testGraphDescriptionDict() throws {
        #if OPENGRAPH_COMPATIBILITY_TEST
        let description = try XCTUnwrap(graphDescription(options: ["format": "graph/dict"] as NSDictionary))
        let dic = Unmanaged<NSDictionary>.fromOpaque(description).takeUnretainedValue()
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
        XCTAssertNil(graphDescription(options: options))
        let graph = graphCreate()
        let description = try XCTUnwrap(graphDescription(graph, options: options))
        let dotGraph = Unmanaged<NSString>.fromOpaque(description).takeUnretainedValue() as String
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
