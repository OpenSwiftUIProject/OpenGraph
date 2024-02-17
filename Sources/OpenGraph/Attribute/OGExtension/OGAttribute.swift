//
//  OGAttribute.swift
//
//
//  Created by Kyle on 2024/2/17.
//

import _OpenGraph

extension OGAttribute {
    @inlinable
    public init<Value>(_ attribute: Attribute<Value>) {
        self = attribute.identifier
    }
    
    @inlinable
    public func unsafeCast<Value>(to type: Value.Type) -> Attribute<Value> {
        fatalError("TODO")
    }
    
    @inlinable
    public static var current: OGAttribute? {
        let current = __OGGraphGetCurrentAttribute()
        return current == .nil ? nil : current
    }
    
    @inlinable
    public func unsafeOffset(at offset: Int) -> OGAttribute {
        create(offset: offset)
    }
    
    @inlinable
    public func setFlags(_ newFlags: OGAttributeFlags, mask: OGAttributeFlags) {
        flags = flags.subtracting(mask).union(newFlags.intersection(mask))
    }
    
    @inlinable
    public func addInput(_ attribute: OGAttribute, options: OGInputOptions, token: Int) {
        __OGGraphAddInput(self, attribute, options, token)
    }
    
    @inlinable
    public func addInput<Value>(_ attribute: Attribute<Value>, options: OGInputOptions, token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
    
    @inlinable
    public func visitBody<Visitor: AttributeBodyVisitor>(_ visitor: inout Visitor) {
        fatalError("TODO")
    }
    
    @inlinable
    public func mutateBody<Value>(as: Value.Type, invalidating: Bool, _ body: (inout Value) -> ()) {
        fatalError("TODO")
    }
    
    @inlinable
    public func breadthFirstSearch(options: OGSearchOptions, _: (OGAttribute) -> Bool) -> Bool {
        fatalError("TODO")
    }
    
    @inlinable
    public var _bodyType: Any.Type { fatalError("TODO") }
    
    @inlinable
    public var _bodyPointer: UnsafeRawPointer { fatalError("TODO") }
    
    @inlinable
    public var valueType: Any.Type { fatalError("TODO") }
        
    @inlinable
    public var indirectDependency: OGAttribute {
        get { fatalError("TODO") }
        set { fatalError("TODO") }
    }
}

// MARK: CustomStringConvertible

extension OGAttribute: CustomStringConvertible {
    @inlinable
    public var description: String { "#\(rawValue)" }
}
