//
//  OGAttribute.swift
//
//
//  Created by Kyle on 2024/2/17.
//

import _OpenGraph

extension OGAttribute {
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
}

// MARK: CustomStringConvertible

extension OGAttribute: CustomStringConvertible {
    @inlinable
    public var description: String { "#\(rawValue)" }
}
