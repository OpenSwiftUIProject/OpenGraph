//
//  OGAttribute.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/17.
//  Lastest Version: iOS 15.5
//  Status: API complete

import _OpenGraph

extension OGAttribute {
    public init<Value>(_ attribute: Attribute<Value>) {
        self = attribute.identifier
    }
    
    public func unsafeCast<Value>(to _: Value.Type) -> Attribute<Value> {
        fatalError("TODO")
    }
    
    public static var current: OGAttribute? {
        let current = __OGGraphGetCurrentAttribute()
        return current == .nil ? nil : current
    }
    
    public func unsafeOffset(at offset: Int) -> OGAttribute {
        create(offset: offset)
    }

    public func setFlags(_ newFlags: OGAttributeFlags, mask: OGAttributeFlags) {
        flags = flags.subtracting(mask).union(newFlags.intersection(mask))
    }

    public func addInput(_ attribute: OGAttribute, options: OGInputOptions, token: Int) {
        __OGGraphAddInput(self, attribute, options, token)
    }

    public func addInput(_ attribute: Attribute<some Any>, options: OGInputOptions, token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
    
    // Question
    public func visitBody(_ visitor: inout some AttributeBodyVisitor) {
        let info = __OGGraphGetAttributeInfo(self)
        let bodyType = info.type.advanced(by: 1).pointee.typeID.type as! _AttributeBody.Type
        bodyType._visitBody(&visitor, info.body)
    }

    public func mutateBody<Value>(as type: Value.Type, invalidating: Bool, _: (inout Value) -> Void) {
        // FIXME: pass body
        __OGGraphMutateAttribute(self, OGTypeID(type), invalidating)
    }
    
    public func breadthFirstSearch(options _: OGSearchOptions, _: (OGAttribute) -> Bool) -> Bool {
        fatalError("TODO")
    }
    
    public var _bodyType: Any.Type {
        __OGGraphGetAttributeInfo(self).type.pointee.typeID.type
    }

    public var _bodyPointer: UnsafeRawPointer {
        __OGGraphGetAttributeInfo(self).body
    }
    
    public var valueType: Any.Type {
        __OGGraphGetAttributeInfo(self).type.pointee.valueTypeID.type
    }

    public var indirectDependency: OGAttribute? {
        get {
            let indirectDependency = __OGGraphGetIndirectDependency(self)
            return indirectDependency == .nil ? nil : indirectDependency
        }
        nonmutating set {
            __OGGraphSetIndirectDependency(self, newValue ?? .nil)
        }
    }
}

// MARK: CustomStringConvertible

extension OGAttribute: CustomStringConvertible {
    @inlinable
    public var description: String { "#\(rawValue)" }
}