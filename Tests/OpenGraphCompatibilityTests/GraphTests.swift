//
//  GraphTests.swift
//  
//
//  Created by Kyle on 2024/1/18.
//

import XCTest
#if OPENGRAPH_COMPATIBILITY_TEST
import AttributeGraph
#else
import OpenGraph
#endif

final class GraphTests: XCTestCase {
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
}
