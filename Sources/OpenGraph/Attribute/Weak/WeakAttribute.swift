//
//  WeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

@propertyWrapper
@dynamicMemberLookup
public struct WeakAttribute<Value> {
    public var base: OGWeakAttribute
    
    public init(base: OGWeakAttribute) {
        self.base = base
    }
    
    public init() {
        base = OGWeakAttribute(raw_attribute: OGAttribute(rawValue: 0), subgraph_id: 0)
    }
    
    public init(_ attribute: Attribute<Value>) {
        base = OGWeakAttribute(attribute: attribute.identifier)
    }
    
    public init(_ attribute: Attribute<Value>?) {
        base = OGWeakAttribute(attribute: attribute?.identifier ?? .nil)
    }
    
    public var wrappedValue: Value? { value }
    
    public var projectedValue: Attribute<Value>?{
        get { attribute }
        _modify { yield &attribute }
    }
    
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member>? {
        attribute?[keyPath: keyPath]
    }
    
    public var attribute: Attribute<Value>? {
        get {
            if let attribute = base.attribute {
                Attribute(identifier: attribute)
            } else {
                nil
            }
        }
        set { // FIXME: _modify
            base = OGWeakAttribute(newValue?.identifier)
        }
    }
    
    public var value: Value? {
        attribute?.value
    }
    
    public func changedValue(options: OGValueOptions) -> (value: Value, changed: Bool)? {
        attribute?.changedValue(options: options)
    }
}

extension WeakAttribute: Hashable {}

extension WeakAttribute: CustomStringConvertible {
    public var description: String { base.description }
}
