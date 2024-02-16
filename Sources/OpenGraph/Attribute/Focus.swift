//
//  Focus.swift
//
//
//  Created by Kyle on 2024/2/16.
//  Lastest Version: iOS 15.5
//  Status: Complete

public struct Focus<Root, Value>: Rule, CustomStringConvertible {
    public var root: Attribute<Root>
    public var keyPath: KeyPath<Root, Value>
    
    @inline(__always)
    public init(root: Attribute<Root>, keyPath: KeyPath<Root, Value>) {
        self.root = root
        self.keyPath = keyPath
    }
    
    // MARK: CustomStringConvertible
    
    @inline(__always)
    public var description: String { "• \(OGTypeID(Self.self).description)" }
    
    // MARK: - Rule
    
    @inline(__always)
    public var value: Value { root.value[keyPath: keyPath] }
    
    // MARK: - _AttributeBody

    @inline(__always)
    public static var flags: OGAttributeTypeFlags { .init() }
}
