//
//  WeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import _OpenGraph

@frozen
@propertyWrapper
@dynamicMemberLookup
public struct WeakAttribute<Value> {
    @usableFromInline
    var base: AnyWeakAttribute
    
    @_alwaysEmitIntoClient
    public init(base: AnyWeakAttribute) {
        self.base = base
    }
    
    public init() {
        base = AnyWeakAttribute(raw_attribute: AnyAttribute(rawValue: 0), subgraph_id: 0)
    }
    
    public init(_ attribute: Attribute<Value>) {
        base = AnyWeakAttribute(attribute.identifier)
    }
    
    public init(_ attribute: Attribute<Value>?) {
        base = AnyWeakAttribute(attribute?.identifier)
    }
    
    public var wrappedValue: Value? { value }
    
    public var projectedValue: Attribute<Value>?{
        get { attribute }
        set { attribute = newValue }
        _modify { yield &attribute }
    }
    
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member>? {
        attribute?[keyPath: keyPath]
    }
    
    public var attribute: Attribute<Value>? {
        get { base.attribute?.unsafeCast(to: Value.self) }
        set { base.attribute = newValue?.identifier }
    }
    
    public var value: Value? {
        attribute?.value
    }
    
    public func changedValue(options: OGValueOptions = []) -> (value: Value, changed: Bool)? {
        attribute?.changedValue(options: options)
    }
}

extension WeakAttribute: Hashable {}

extension WeakAttribute: CustomStringConvertible {
    public var description: String { base.description }
}
