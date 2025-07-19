//
//  External.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

@frozen
public struct External<Value> {
    public init() {}
}

// MARK: - _AttributeBody

extension External: _AttributeBody {
    public static var comparisonMode: ComparisonMode { .equatableAlways }

    public static var flags: Flags { [] }

    public static func _update(_: UnsafeMutableRawPointer, attribute _: AnyAttribute) {}
}

// MARK: CustomStringConvertible

extension External: CustomStringConvertible {
    public var description: String { Metadata(Value.self).description }
}
