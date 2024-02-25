//
//  Focus.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/16.
//  Lastest Version: iOS 15.5
//  Status: Complete

public struct Focus<Root, Value> {
    public var root: Attribute<Root>
    public var keyPath: KeyPath<Root, Value>
    
    public init(root: Attribute<Root>, keyPath: KeyPath<Root, Value>) {
        self.root = root
        self.keyPath = keyPath
    }
}

// MARK: - Rule

extension Focus: Rule {
    public var value: Value { root.value[keyPath: keyPath] }
    public static var flags: OGAttributeTypeFlags { [] }
}

// MARK: CustomStringConvertible

extension Focus: CustomStringConvertible {
    public var description: String { "• \(OGTypeID(Value.self).description)" }
}
