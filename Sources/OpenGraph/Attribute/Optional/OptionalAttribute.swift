//
//  OptionalAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

@frozen
@propertyWrapper
@dynamicMemberLookup
public struct OptionalAttribute<Value> {
    public var base: AnyOptionalAttribute
    
    public init() {
        base = AnyOptionalAttribute()
    }
    
    public init(base: AnyOptionalAttribute) {
        self.base = base
    }
    
    public init(_ attribute: Attribute<Value>) {
        base = AnyOptionalAttribute(attribute.identifier)
    }
    
    public init(_ attribute: Attribute<Value>?) {
        base = AnyOptionalAttribute(attribute?.identifier)
    }
    
    public init(_ weakAttribute: WeakAttribute<Value>) {
        base = AnyOptionalAttribute(weakAttribute.base)
    }
    
    public var attribute: Attribute<Value>? {
        get { base.attribute?.unsafeCast(to: Value.self) }
        set { base.attribute = newValue?.identifier }
        _modify {
            var value = attribute
            yield &value
            attribute = value
        }
    }
    
    public var value: Value? { attribute?.value }
    
    public func changedValue(options: OGValueOptions) -> (value: Value, changed: Bool)? {
        attribute?.changedValue(options: options)
    }
    
    public func map<V>(_ body: (Attribute<Value>) -> V) -> V? {
        if let attribute { body(attribute) } else { nil }
    }
    
    public var wrappedValue: Value? { value }
    
    public var projectedValue: Attribute<Value>? {
        get { attribute }
        set { attribute = newValue }
        _modify { yield &attribute }
    }
    
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member>? {
        attribute?[keyPath: keyPath]
    }
}

extension OptionalAttribute: Hashable {}

extension OptionalAttribute: CustomStringConvertible {
    public var description: String { attribute?.description ?? "nil" }
}
