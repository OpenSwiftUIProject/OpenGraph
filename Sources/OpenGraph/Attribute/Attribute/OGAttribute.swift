//
//  OGAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: API complete

import _OpenGraph

extension OGAttribute {
    public init<Value>(_ attribute: Attribute<Value>) {
        self = attribute.identifier
    }
    
    public func unsafeCast<Value>(to _: Value.Type) -> Attribute<Value> {
        Attribute<Value>(identifier: self)
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

    public func addInput(_ attribute: OGAttribute, options: OGInputOptions = [], token: Int) {
        __OGGraphAddInput(self, attribute, options, token)
    }

    public func addInput<Value>(_ attribute: Attribute<Value>, options: OGInputOptions = [], token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
    
    // FIXME: Use AttributeType instead
    public func visitBody<Body: AttributeBodyVisitor>(_ visitor: inout Body) {
        let bodyType = info.type.advanced(by: 1).pointee.typeID.type as! _AttributeBody.Type
        bodyType._visitBody(&visitor, info.body)
    }

    public func mutateBody<Value>(as type: Value.Type, invalidating: Bool, _ body: (inout Value) -> Void) {
        OGAttribute.mutateAttribute(self, type: OGTypeID(type), invalidating: invalidating) { value in
            body(&value.assumingMemoryBound(to: Value.self).pointee)
        }
    }
    
    public func breadthFirstSearch(options _: OGSearchOptions = [], _: (OGAttribute) -> Bool) -> Bool {
        fatalError("TODO")
    }
    
    public var _bodyType: Any.Type {
        info.type.pointee.typeID.type
    }

    public var _bodyPointer: UnsafeRawPointer {
        info.body
    }
    
    public var valueType: Any.Type {
        info.type.pointee.valueTypeID.type
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

public typealias AttributeUpdateBlock = () -> (UnsafeMutableRawPointer, OGAttribute) -> Void

// FIXME: migrate to use @_extern(c, "xx") in Swift 6
extension OGAttribute {
    @_silgen_name("OGGraphMutateAttribute")
    private static func mutateAttribute(
        _ attribute: OGAttribute,
        type: OGTypeID,
        invalidating: Bool,
        body: (UnsafeMutableRawPointer) -> Void
    )
}
