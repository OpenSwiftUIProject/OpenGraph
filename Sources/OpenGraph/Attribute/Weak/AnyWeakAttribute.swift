//
//  AnyWeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

public typealias AnyWeakAttribute = OGWeakAttribute

extension AnyWeakAttribute {
    @_alwaysEmitIntoClient
    public init(_ attribute: AnyAttribute?) {
        self = __OGCreateWeakAttribute(attribute ?? .nil)
    }
    
    @_alwaysEmitIntoClient
    public init<Value>(_ weakAttribute: WeakAttribute<Value>) {
        self = weakAttribute.base
    }
    
    @_alwaysEmitIntoClient
    public func unsafeCast<Value>(to _: Value.Type) -> WeakAttribute<Value> {
        WeakAttribute(base: self)
    }
    
    @_alwaysEmitIntoClient
    public var attribute: AnyAttribute? {
        get {
            let attribute = __OGWeakAttributeGetAttribute(self)
            return attribute == .nil ? nil : attribute
        }
        set {
            self = AnyWeakAttribute(newValue)
        }
    }
}

extension AnyWeakAttribute: Swift.Hashable {
    @_alwaysEmitIntoClient
    public static func == (lhs: AnyWeakAttribute, rhs: AnyWeakAttribute) -> Bool {
        lhs.raw_attribute == rhs.raw_attribute && lhs.subgraph_id == rhs.subgraph_id
    }
    
    @_alwaysEmitIntoClient
    public func hash(into hasher: inout Hasher) {
        hasher.combine(raw_attribute)
        hasher.combine(subgraph_id)
    }
    
    @_alwaysEmitIntoClient
    public var hashValue: Int {
        _hashValue(for: self)
    }
}

extension AnyWeakAttribute: Swift.CustomStringConvertible {
    @_alwaysEmitIntoClient
    public var description: String { attribute?.description ?? "nil" }
}
