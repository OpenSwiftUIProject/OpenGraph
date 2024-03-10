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
    public let identifier: OGAttribute
    
    public init(source: Attribute<Value>) {
        identifier = source.identifier.createIndirect(size: UInt64(MemoryLayout<Value>.size))
    }
    
    public var source: Attribute<Value> {
        get {
            Attribute(identifier: __OGGraphGetIndirectAttribute(identifier))
        }
        nonmutating set { __OGGraphSetIndirectAttribute(identifier, newValue.identifier) }
        nonmutating _modify {
            var value = source
            yield &value
            source = value
        }
    }
    
    public var dependency: OGAttribute? {
        get {
            let dependency = __OGGraphGetIndirectDependency(identifier)
            return dependency == .nil ? nil : dependency
        }
        nonmutating set {__OGGraphSetIndirectDependency(identifier, newValue ?? .nil) }
        nonmutating _modify {
            var value = dependency
            yield &value
            dependency = value
        }
    }
    
    public var value: Value {
        get { Attribute(identifier: identifier).value }
        nonmutating set { Attribute(identifier: identifier).value = newValue }
        // FIXME
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
