//
//  Focus.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

@frozen
public struct Focus<Root, Value>: Rule, CustomStringConvertible {
    public var root: Attribute<Root>
    public var keyPath: KeyPath<Root, Value>
    
    public init(root: Attribute<Root>, keyPath: KeyPath<Root, Value>) {
        self.root = root
        self.keyPath = keyPath
    }

    public var value: Value { root.value[keyPath: keyPath] }

    public static var flags: Flags { [] }

    public var description: String { "• \(Metadata(Value.self).description)" }
}
