//
//  IndirectAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

@frozen
@propertyWrapper
@dynamicMemberLookup
public struct IndirectAttribute<Value> {
    public let identifier: AnyAttribute
    
    public init(source: Attribute<Value>) {
        identifier = source.identifier.createIndirect(size: UInt64(MemoryLayout<Value>.size))
    }
    
    public var source: Attribute<Value> {
        get { Attribute(identifier: identifier.source) }
        nonmutating set { identifier.source = newValue.identifier }
    }
    
    public var dependency: AnyAttribute? {
        get {
            let dependency = identifier._indirectDependency
            return dependency == .nil ? nil : dependency
        }
        nonmutating set { identifier._indirectDependency = newValue ?? .nil }
    }
    
    public var value: Value {
        get { Attribute(identifier: identifier).value }
        nonmutating set { Attribute(identifier: identifier).value = newValue }
        nonmutating _modify { yield &Attribute<Value>(identifier: identifier).value }
    }
    
    public func changedValue(options: OGValueOptions = []) -> (value: Value, changed: Bool) {
        Attribute(identifier: identifier).changedValue(options: options)
    }
    
    public var wrappedValue: Value {
        get { value }
        nonmutating set { value = newValue }
        nonmutating _modify { yield &value }
    }
    
    public var projectedValue: Attribute<Value> {
        Attribute(identifier: identifier)
    }
    
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        Attribute(identifier: identifier)[dynamicMember: keyPath]
    }
}

extension IndirectAttribute: Hashable {}
