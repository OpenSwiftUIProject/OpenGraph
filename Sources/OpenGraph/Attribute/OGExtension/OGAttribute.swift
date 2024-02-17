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
        let current = _current
        return current == .nil ? .nil : current
    }
    
    @inlinable
    public func unsafeOffset(at offset: Int) -> OGAttribute {
        create(offset: UInt64(offset))
    }
    
    @inlinable
    public func setFlags(_ newFlags: OGAttributeFlags, mask: OGAttributeFlags) {
        flags = flags.subtracting(mask).union(newFlags.intersection(mask))
    }
}

// MARK: CustomStringConvertible

extension OGAttribute: CustomStringConvertible {
    @inlinable
    public var description: String { "#\(rawValue)" }
}
