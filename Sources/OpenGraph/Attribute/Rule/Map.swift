//
//  Map.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

// MARK: - Map

@frozen
public struct Map<Source, Value>: Rule, CustomStringConvertible {
    public var arg: Attribute<Source>
    public let body: (Source) -> Value

    public init(_ arg: Attribute<Source>, _ body: @escaping (Source) -> Value) {
        self.arg = arg
        self.body = body
    }

    public var value: Value { body(arg.value) }

    public static var flags: _AttributeType.Flags { [] }

    public var description: String { "λ \(Value.self)" }
}
