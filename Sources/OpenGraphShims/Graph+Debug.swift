//
//  Graph+Debug.swift
//  OpenGraphShims

#if canImport(Darwin)

import Foundation

@_spi(Debug)
extension Graph {
    public var dict: [String: Any]? {
        let options = ["format": "graph/dict"] as NSDictionary
        guard let description = Graph.description(nil, options: options) else {
            return nil
        }
        guard let dictionary = description.takeUnretainedValue() as? NSDictionary else {
            return nil
        }
        return dictionary as? [String: Any]
    }

    // style:
    // - bold: empty input/output edge
    // - dashed: indirect or has no value
    // color:
    // - red: is_changed
    public var dot: String? {
        let options = ["format": "graph/dot"] as NSDictionary
        guard let description = Graph.description(self, options: options)
        else {
            return nil
        }
        return description.takeUnretainedValue() as? String
    }
}

#endif
