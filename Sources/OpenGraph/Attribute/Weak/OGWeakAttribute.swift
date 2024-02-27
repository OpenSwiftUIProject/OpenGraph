//
//  OGWeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

extension OGWeakAttribute {
    public init(_ attribute: OGAttribute?) {
        self.init(attribute: attribute ?? .nil)
    }
    
    public init<Value>(_ weakAttribute: WeakAttribute<Value>) {
        self = weakAttribute.base
    }
    
    public func unsafeCast<Value>(to _: Value.Type) -> WeakAttribute<Value> {
        WeakAttribute(base: self)
    }
    
    public var attribute: OGAttribute? {
        get {
            let attribute = _attribute
            return attribute == .nil ? nil : attribute
        }
        set { // FIXME: _modify
            self = OGWeakAttribute(newValue)
        }
    }
}

extension OGWeakAttribute: Hashable {
    public static func == (lhs: OGWeakAttribute, rhs: OGWeakAttribute) -> Bool {
        lhs.raw_attribute == rhs.raw_attribute && lhs.subgraph_id == rhs.subgraph_id
    }
    
    public func hash(into hasher: inout Hasher) {
        hasher.combine(raw_attribute)
        hasher.combine(subgraph_id)
    }
}

extension OGWeakAttribute: CustomStringConvertible {
    public var description: String { attribute?.description ?? "nil" }
}
