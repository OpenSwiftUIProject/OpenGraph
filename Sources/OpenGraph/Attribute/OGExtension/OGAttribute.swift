//
//  OGAttribute.swift
//
//
//  Created by Kyle on 2024/2/17.
//

import _OpenGraph

// MARK: CustomStringConvertible

extension OGAttribute: CustomStringConvertible {
    public var description: String { "#\(rawValue)" }
}
