//
//  OGAttribute.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/17.
//  Lastest Version: iOS 15.5
//  Status: API complete

import _OpenGraph

extension OGAttribute {
    @inlinable
    @inline(__always)
    public init<Value>(_ attribute: Attribute<Value>) {
        self = attribute.identifier
    }
    
    @inlinable
    @inline(__always)
    public func unsafeCast<Value>(to type: Value.Type) -> Attribute<Value> {
        fatalError("TODO")
    }
    
    @inlinable
    @inline(__always)
    public static var current: OGAttribute? {
        let current = __OGGraphGetCurrentAttribute()
        return current == .nil ? nil : current
    }
    
    @inlinable
    @inline(__always)
    public func unsafeOffset(at offset: Int) -> OGAttribute {
        create(offset: offset)
    }
    
    @inlinable
    @inline(__always)
    public func setFlags(_ newFlags: OGAttributeFlags, mask: OGAttributeFlags) {
        flags = flags.subtracting(mask).union(newFlags.intersection(mask))
    }
    
    @inlinable
    @inline(__always)
    public func addInput(_ attribute: OGAttribute, options: OGInputOptions, token: Int) {
        __OGGraphAddInput(self, attribute, options, token)
    }
    
    @inlinable
    @inline(__always)
    public func addInput<Value>(_ attribute: Attribute<Value>, options: OGInputOptions, token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
    
    @inlinable
    @inline(__always)
    public func visitBody<Visitor: AttributeBodyVisitor>(_ visitor: inout Visitor) {
        fatalError("TODO")
    }
    
    @inlinable
    @inline(__always)
    public func mutateBody<Value>(as: Value.Type, invalidating: Bool, _ body: (inout Value) -> ()) {
        fatalError("TODO")
    }
    
    @inlinable
    @inline(__always)
    public func breadthFirstSearch(options: OGSearchOptions, _: (OGAttribute) -> Bool) -> Bool {
        fatalError("TODO")
    }
    
    @inlinable
    @inline(__always)
    public var _bodyType: Any.Type {
        __OGGraphGetAttributeInfo(self).type.pointee.typeID.type
    }
    
    @inlinable
    @inline(__always)
    public var _bodyPointer: UnsafeRawPointer {
        __OGGraphGetAttributeInfo(self).body
    }
    
    @inlinable
    @inline(__always)
    public var valueType: Any.Type {
        __OGGraphGetAttributeInfo(self).type.pointee.valueTypeID.type
    }
        
    @inlinable
    @inline(__always)
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
