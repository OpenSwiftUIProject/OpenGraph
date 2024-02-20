import _OpenGraph

@frozen
@propertyWrapper
@dynamicMemberLookup
public struct Attribute<Value> {
    public var identifier: OGAttribute
    
    // MARK: - Initializer
    
    public init(identifier: OGAttribute) {
        self.identifier = identifier
    }

    public init(_ attribute: Attribute<Value>) {
        self = attribute
    }
        
    public init(value: Value) {
        self = withUnsafePointer(to: value) { valuePointer in
            withUnsafePointer(to: External<Value>()) { bodyPointer in
                Attribute(body: bodyPointer, value: valuePointer, flags: ._16) {
                    External<Value>._update
                }
            }
        }
    }
    
    public init(type _: Value.Type) {
        self = withUnsafePointer(to: External<Value>()) { bodyPointer in
            Attribute(body: bodyPointer, value: nil, flags: ._16) {
                External<Value>._update
            }
        }
    }

    public init<Body: _AttributeBody>(
        body: UnsafePointer<Body>,
        value: UnsafePointer<Value>?,
        flags: OGAttributeTypeFlags,
        update: AttributeUpdateBlock
    ) {
        #if os(WASI)
        // This is a compiler issue and SwiftWasm toolchain enable the assertation
        // See https://github.com/swiftwasm/swift/issues/5569
        fatalError("Swift 5.9.1 Compiler issue - type mismatch of Unmanaged<OGGraphContext> and OGGraphContext")
        #else
        guard let context = OGSubgraph.currentGraphContext else {
            fatalError("attempting to create attribute with no subgraph: \(Value.self)")
        }
        let index = OGGraph.typeIndex(
            ctx: context,
            body: Body.self,
            valueType: OGTypeID(Value.self),
            flags: flags,
            update: update
        )
        identifier = __OGGraphCreateAttribute(index, body, value)
        #endif
    }
    
    // MARK: - propertyWrapper
        
    public var wrappedValue: Value {
        unsafeAddress {
            __OGGraphGetValue(identifier, [], OGTypeID(Value.self))
                .value
                .assumingMemoryBound(to: Value.self)
        }
        set { _ = setValue(newValue) }
    }
    
    public var projectedValue: Attribute<Value> {
        get { Attribute(identifier: identifier) }
        _modify { yield &self }
    }

    // MARK: - dynamicMemberLookup
        
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        self[keyPath: keyPath]
    }
    
    public subscript<Member>(keyPath keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        if let offset = MemoryLayout<Value>.offset(of: keyPath) {
            let identifier = identifier.create(offset: offset, size: numericCast(MemoryLayout<Member>.size))
            return Attribute<Member>(identifier: identifier)
        } else {
            _ = Focus(root: self, keyPath: keyPath)
            fatalError()
        }
    }
        
    public subscript<Member>(offset body: (inout Value) -> PointerOffset<Value, Member>) -> Attribute<Member> {
        let offset = PointerOffset.offset(body)
        let identifier = identifier.create(offset: offset.byteOffset, size: numericCast(MemoryLayout<Member>.size))
        return Attribute<Member>(identifier: identifier)
    }
    
    // MARK: - Value
    
    public var value: Value {
        unsafeAddress {
            __OGGraphGetValue(identifier, [], OGTypeID(Value.self))
                .value
                .assumingMemoryBound(to: Value.self)
        }
        set { _ = setValue(newValue) }
    }
    
    public func changedValue(options: OGValueOptions) -> (value: Value, changed: Bool) {
        let value = __OGGraphGetValue(identifier, options, OGTypeID(Value.self))
        return (
            value.value.assumingMemoryBound(to: Value.self).pointee,
            value.changed
        )
    }
    
    public func setValue(_ value: Value) -> Bool {
        withUnsafePointer(to: value) { valuePointer in
            __OGGraphSetValue(identifier, valuePointer, OGTypeID(Value.self))
        }
    }

    // MARK: - Input
    
    public func addInput(_ attribute: OGAttribute, options: OGInputOptions, token: Int) {
        __OGGraphAddInput(self.identifier, attribute, options, token)
    }
    
    public func addInput<V>(_ attribute: Attribute<V>, options: OGInputOptions, token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
}

extension Attribute: Hashable {}

extension Attribute: CustomStringConvertible {
    public var description: String {
        identifier.description
    }
}

// MARK: Attribute + Rule

extension Attribute {
    // init with Rule and StatefulRule
}

// TODO:
private struct AttributeType {
    var graphType: OGAttributeType
    var type: _AttributeBody.Type
}
