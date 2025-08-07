//
//  WeakAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

public import OpenGraphCxx

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
        base = AnyWeakAttribute(_details: AnyWeakAttribute.__Unnamed_struct__details(identifier: AnyAttribute(rawValue: 0), seed: 0))
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
        OGGraphGetWeakValue(base, type: Value.self)
            .value
            // TO BE CONFIRMED
            .assumingMemoryBound(to: Value?.self)
            .pointee
    }
    
    public func changedValue(options: OGValueOptions = []) -> (value: Value, changed: Bool)? {
        attribute?.changedValue(options: options)
    }
}

extension WeakAttribute: Hashable {}

extension WeakAttribute: CustomStringConvertible {
    public var description: String { base.description }
}

@_silgen_name("OGGraphGetWeakValue")
@inline(__always)
@inlinable
func OGGraphGetWeakValue<Value>(_ attribute: AnyWeakAttribute, options: OGValueOptions = [], type: Value.Type = Value.self) -> OGValue
