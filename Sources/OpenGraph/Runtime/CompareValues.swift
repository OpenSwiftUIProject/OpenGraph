//
//  CompareValues.swift
//  OpenGraph
//
//  Created by Kyle on 2024/1/9.
//  Lastest Version: iOS 15.5
//  Status: Complete

import _OpenGraph

@_silgen_name("OGCompareValues")
@inlinable
@inline(__always)
func OGCompareValues(lhs: UnsafeRawPointer,
                            rhs: UnsafeRawPointer,
                            options: OGComparisonOptions,
                            type: Any.Type) -> Bool

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, mode: OGComparisonMode = ._3) -> Bool {
    withUnsafePointer(to: lhs) { p1 in
        withUnsafePointer(to: rhs) { p2 in
            OGCompareValues(lhs: p1, rhs: p2, options: .init(mode: mode), type: Value.self)
        }
    }
}

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, options: OGComparisonOptions) -> Bool {
    withUnsafePointer(to: lhs) { p1 in
        withUnsafePointer(to: rhs) { p2 in
            OGCompareValues(lhs: p1, rhs: p2, options: options, type: Value.self)
        }
    }
}

extension OGComparisonOptions {
    public init(mode: OGComparisonMode) {
        self.init(rawValue: mode.rawValue)
    }
}
