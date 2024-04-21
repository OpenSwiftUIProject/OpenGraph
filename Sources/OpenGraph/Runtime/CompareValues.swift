//
//  CompareValues.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

@_silgen_name("OGCompareValues")
private func OGCompareValues(
    lhs: UnsafeRawPointer,
    rhs: UnsafeRawPointer,
    type: Any.Type,
    options: OGComparisonOptions
) -> Bool

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, mode: OGComparisonMode = ._3) -> Bool {
    compareValues(lhs, rhs, options: OGComparisonOptions(mode: mode))
}

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, options: OGComparisonOptions) -> Bool {
    withUnsafePointer(to: lhs) { p1 in
        withUnsafePointer(to: rhs) { p2 in
            OGCompareValues(lhs: p1, rhs: p2, type: Value.self, options: options)
        }
    }
}

extension OGComparisonOptions {
    public init(mode: OGComparisonMode) {
        self.init(rawValue: mode.rawValue)
    }
}
