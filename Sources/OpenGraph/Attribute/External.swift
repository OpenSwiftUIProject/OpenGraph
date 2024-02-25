//
//  External.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/16.
//  Lastest Version: iOS 15.5
//  Status: Complete

@frozen
public struct External<Value> {
    public init() {}
}

// MARK: - _AttributeBody

extension External: _AttributeBody {
    public static var comparisonMode: OGComparisonMode { ._3 }
    public static var flags: OGAttributeTypeFlags { [] }
    public static func _update(_: UnsafeMutableRawPointer, attribute _: OGAttribute) {}
}

// MARK: CustomStringConvertible

extension External: CustomStringConvertible {
    public var description: String { OGTypeID(Value.self).description }
}
