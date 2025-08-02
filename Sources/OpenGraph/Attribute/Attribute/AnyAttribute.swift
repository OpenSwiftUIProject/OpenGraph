//
//  AnyAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: API complete

public import OpenGraphCxx

@_silgen_name("OGGraphMutateAttribute")
private func OGGraphMutateAttribute(
    _ attribute: AnyAttribute,
    type: Metadata,
    invalidating: Bool,
    body: (UnsafeMutableRawPointer) -> Void
)

extension AnyAttribute {
    public init<Value>(_ attribute: Attribute<Value>) {
        self = attribute.identifier
    }
    
    public func unsafeCast<Value>(to _: Value.Type) -> Attribute<Value> {
        Attribute<Value>(identifier: self)
    }
    
    public static var current: AnyAttribute? {
        let current = __OGGraphGetCurrentAttribute()
        return current == .nil ? nil : current
    }
    
    public func unsafeOffset(at offset: Int) -> AnyAttribute {
        create(offset: offset)
    }

    public func setFlags(_ newFlags: Subgraph.Flags, mask: Subgraph.Flags) {
        flags = flags.subtracting(mask).union(newFlags.intersection(mask))
    }

    public func addInput(_ attribute: AnyAttribute, options: OGInputOptions = [], token: Int) {
        __OGGraphAddInput(self, attribute, options, token)
    }

    public func addInput<Value>(_ attribute: Attribute<Value>, options: OGInputOptions = [], token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
    
    // FIXME: Use AttributeType instead
    public func visitBody<Body: AttributeBodyVisitor>(_ visitor: inout Body) {
        let bodyType = info.type.advanced(by: 1).pointee.self_id.type as! _AttributeBody.Type
        bodyType._visitBody(&visitor, info.body)
    }

    public func mutateBody<Value>(as type: Value.Type, invalidating: Bool, _ body: (inout Value) -> Void) {
        OGGraphMutateAttribute(
            self,
            type: Metadata(type),
            invalidating: invalidating
        ) { value in
            body(&value.assumingMemoryBound(to: Value.self).pointee)
        }
    }
    
    public func breadthFirstSearch(options _: SearchOptions = [], _: (AnyAttribute) -> Bool) -> Bool {
        fatalError("TODO")
    }
    
    public var _bodyType: Any.Type {
        info.type.pointee.self_id.type
    }

    public var _bodyPointer: UnsafeRawPointer {
        info.body
    }

    public var valueType: Any.Type {
        info.type.pointee.value_id.type
    }

    public var indirectDependency: AnyAttribute? {
        get {
            let indirectDependency = _indirectDependency
            return indirectDependency == .nil ? nil : indirectDependency
        }
        nonmutating set {
            _indirectDependency = newValue ?? .nil
        }
    }    
}

// MARK: CustomStringConvertible

extension AnyAttribute: Swift.CustomStringConvertible {
    @inlinable
    public var description: String { "#\(rawValue)" }
}

public typealias AttributeUpdateBlock = () -> (UnsafeMutableRawPointer, AnyAttribute) -> Void

extension [AnyAttribute] {
    @_transparent
    public var anyInputsChanged: Bool {
        __OGGraphAnyInputsChanged(self, count)
    }
}
