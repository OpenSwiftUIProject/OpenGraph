//
//  External.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/16.
//  Lastest Version: iOS 15.5
//  Status: Complete

@frozen
public struct External<Value>: _AttributeBody, CustomStringConvertible {
    public init() {}
    
    // MARK: CustomStringConvertible
    
    @inline(__always)
    public var description: String { OGTypeID(Self.self).description }
    
    // MARK: - _AttributeBody

    @inline(__always)
    public static var comparisonMode: OGComparisonMode { ._3 }
        
    @inline(__always)
    public static var flags: OGAttributeTypeFlags { .init() }
    
    @inline(__always)
    public static func _update(_: UnsafeMutableRawPointer, attribute _: OGAttribute) {}
}
