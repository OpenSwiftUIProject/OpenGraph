//
//  AnyOptionalAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

@frozen
public struct AnyOptionalAttribute {
    public var identifier: OGAttribute
    
    public init() {
        identifier = .nil
    }
    
    public init(_ attribute: OGAttribute) {
        identifier = attribute
    }
    
    public init(_ attribute: OGAttribute?) {
        identifier = attribute ?? .nil
    }
    
    init(_ weakAttribute: OGWeakAttribute) {
        identifier = __OGWeakAttributeGetAttribute(weakAttribute)
    }
    
    public init<Value>(_ attribute: OptionalAttribute<Value>) {
        self = attribute.base
    }
    
    public static var current: AnyOptionalAttribute {
        AnyOptionalAttribute(__OGGraphGetCurrentAttribute())
    }
    
    public var attribute: OGAttribute? {
        get { identifier == .nil ? nil : identifier }
        set { identifier = newValue ?? .nil }
    }
    
    public func map<Value>(_ body: (OGAttribute) -> Value) -> Value? {
        if let attribute { body(attribute) } else { nil }
    }
    
    public func unsafeCast<Value>(to _: Value.Type) -> OptionalAttribute<Value> {
        OptionalAttribute(base: self)
    }
}

extension AnyOptionalAttribute: Hashable {}

extension AnyOptionalAttribute: CustomStringConvertible {
    public var description: String {
        attribute?.description ?? "nil"
    }
}
