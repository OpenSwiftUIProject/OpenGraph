//
//  OGWeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

extension OGWeakAttribute {
    @_alwaysEmitIntoClient
    public init(_ attribute: OGAttribute?) {
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
    public var attribute: OGAttribute? {
        get {
            let attribute = __OGWeakAttributeGetAttribute(self)
            return attribute == .nil ? nil : attribute
        }
        set {
            self = OGWeakAttribute(newValue)
        }
    }
}

extension OGWeakAttribute: Swift.Hashable {
    @_alwaysEmitIntoClient
    public static func == (lhs: OGWeakAttribute, rhs: OGWeakAttribute) -> Bool {
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

extension OGWeakAttribute: Swift.CustomStringConvertible {
    @_alwaysEmitIntoClient
    public var description: String { attribute?.description ?? "nil" }
}
