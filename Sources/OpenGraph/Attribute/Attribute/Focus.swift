//
//  Focus.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
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
    public var description: String { "• \(Metadata(Value.self).description)" }
}
