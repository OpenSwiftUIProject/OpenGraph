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
    public static var comparisonMode: OGComparisonMode { ._3 }
    public static var flags: OGAttributeTypeFlags { [] }
    public static func _update(_: UnsafeMutableRawPointer, attribute _: AnyAttribute) {}
}

// MARK: CustomStringConvertible

extension External: CustomStringConvertible {
    public var description: String { OGTypeID(Value.self).description }
}
