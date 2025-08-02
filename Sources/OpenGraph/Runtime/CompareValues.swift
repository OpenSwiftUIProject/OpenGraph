//
//  CompareValues.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

public import OpenGraphCxx

@_silgen_name("OGCompareValues")
private func OGCompareValues(
    lhs: UnsafeRawPointer,
    rhs: UnsafeRawPointer,
    type: Any.Type,
    options: ComparisonOptions
) -> Bool

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, mode: ComparisonMode = .equatableAlways) -> Bool {
    compareValues(lhs, rhs, options: [.init(mode: mode), .copyOnWrite])
}

public func compareValues<Value>(_ lhs: Value, _ rhs: Value, options: ComparisonOptions) -> Bool {
    withUnsafePointer(to: lhs) { p1 in
        withUnsafePointer(to: rhs) { p2 in
            OGCompareValues(lhs: p1, rhs: p2, type: Value.self, options: options)
        }
    }
}

extension ComparisonOptions {
    public init(mode: ComparisonMode) {
        self.init(rawValue: numericCast(mode.rawValue))
    }
}
