//
//  OGWeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

extension OGWeakAttribute {
    init(_ attribute: OGAttribute?) {
        self = __OGCreateWeakAttribute(attribute ?? .nil)
    }
    
    init<Value>(_ weakAttribute: WeakAttribute<Value>) {
        self = weakAttribute.base
    }
    
    func unsafeCast<Value>(to _: Value.Type) -> WeakAttribute<Value> {
        WeakAttribute(base: self)
    }
    
    var attribute: OGAttribute? {
        get {
            let attribute = __OGWeakAttributeGetAttribute(self)
            return attribute == .nil ? nil : attribute
        }
        set {
            self = OGWeakAttribute(newValue)
        }
        _modify {
            var value = attribute
            yield &value
            attribute = value
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
