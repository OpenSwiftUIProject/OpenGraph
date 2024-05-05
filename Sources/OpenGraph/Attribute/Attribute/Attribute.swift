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
        flags: OGAttributeTypeFlags = [],
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
        identifier = OGGraphCreateAttribute(index: index, body: body, value: value)
        #endif
    }
    
    // MARK: - propertyWrapper
        
    public var wrappedValue: Value {
        unsafeAddress {
            OGGraphGetValue(identifier, type: Value.self)
                .value
                .assumingMemoryBound(to: Value.self)
        }
        nonmutating set { _ = setValue(newValue) }
    }
    
    public var projectedValue: Attribute<Value> {
        get { self }
        set { self = newValue }
    }

    // MARK: - dynamicMemberLookup
        
    public subscript<Member>(dynamicMember keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        self[keyPath: keyPath]
    }
    
    public subscript<Member>(keyPath keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        if let offset = MemoryLayout<Value>.offset(of: keyPath) {
            return unsafeOffset(at: offset, as: Member.self)
        } else {
            return Attribute<Member>(Focus(root: self, keyPath: keyPath))
        }
    }
        
    public subscript<Member>(offset body: (inout Value) -> PointerOffset<Value, Member>) -> Attribute<Member> {
        unsafeOffset(at: PointerOffset.offset(body).byteOffset, as: Member.self)
    }
    
    // MARK: - Transform
    
    public func unsafeCast<V>(to type: V.Type) -> Attribute<V> {
        identifier.unsafeCast(to: type)
    }
    
    public func unsafeOffset<Member>(at offset: Int, as _: Member.Type) -> Attribute<Member> {
        Attribute<Member>(
            identifier: identifier.create(
                offset: offset,
                size: numericCast(MemoryLayout<Member>.size)
            )
        )
    }
    
    public func applying<Member>(offset: PointerOffset<Value, Member>) -> Attribute<Member> {
        unsafeOffset(at: offset.byteOffset, as: Member.self)
    }
    
    public func visitBody<Body: AttributeBodyVisitor>(_ visitor: inout Body) {
        identifier.visitBody(&visitor)
    }
    
    public func mutateBody<V>(as type: V.Type, invalidating: Bool, _ body: (inout V) -> Void) {
        identifier.mutateBody(as: type, invalidating: invalidating, body)
    }

    public func breadthFirstSearch(options: OGSearchOptions = [], _ body: (OGAttribute) -> Bool) -> Bool {
        identifier.breadthFirstSearch(options: options, body)
    }
    
    // MARK: - Graph
    
    public var graph: OGGraph {
        #if os(WASI)
        fatalError("Compiler Bug")
        #else
        identifier.graph
        #endif
    }
    public var subgraph: OGSubgraph {
        #if os(WASI)
        fatalError("Compiler Bug")
        #else
        identifier.subgraph
        #endif
    }
    
    // MARK: - Value
    
    public var value: Value {
        unsafeAddress {
            OGGraphGetValue(identifier, type: Value.self)
                .value
                .assumingMemoryBound(to: Value.self)
        }
        nonmutating set { _ = setValue(newValue) }
    }
    
    public var valueState: OGValueState { identifier.valueState }
    
    public func valueAndFlags(options: OGValueOptions = []) -> (value: Value, flags: OGChangedValueFlags) {
        let value = OGGraphGetValue(identifier, options: options, type: Value.self)
        return (
            value.value.assumingMemoryBound(to: Value.self).pointee,
            value.changed ? ._1 : []
        )
    }
    
    public func changedValue(options: OGValueOptions = []) -> (value: Value, changed: Bool) {
        let value = OGGraphGetValue(identifier, options: options, type: Value.self)
        return (
            value.value.assumingMemoryBound(to: Value.self).pointee,
            value.changed
        )
    }
    
    public func setValue(_ value: Value) -> Bool {
        withUnsafePointer(to: value) { valuePointer in
            OGGraphSetValue(identifier, valuePointer: valuePointer)
        }
    }
    
    public var hasValue: Bool { identifier.hasValue }
    public func updateValue() { identifier.updateValue() }
    public func prefetchValue() { identifier.prefetchValue() }
    public func invalidateValue() { identifier.invalidateValue() }
    public func validate() { identifier.verify(type: OGTypeID(Value.self)) }

    // MARK: - Input
    
    public func addInput(_ attribute: OGAttribute, options: OGInputOptions = [], token: Int) {
        identifier.addInput(attribute, options: options, token: token)
    }
    
    public func addInput<V>(_ attribute: Attribute<V>, options: OGInputOptions = [], token: Int) {
        identifier.addInput(attribute, options: options, token: token)
    }
    
    // MARK: - Flags

    public var flags: OGAttributeFlags {
        get { identifier.flags }
        nonmutating set { identifier.flags = newValue }
    }
    
    public func setFlags(_ newFlags: OGAttributeFlags, mask: OGAttributeFlags) {
        identifier.setFlags(newFlags, mask: mask)
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
    public init<R: Rule>(_ rule: R) where R.Value == Value {
        self = withUnsafePointer(to: rule) { pointer in
            Attribute(body: pointer, value: nil) { R._update }
        }
    }
    
    public init<R: StatefulRule>(_ rule: R) where R.Value == Value {
        self = withUnsafePointer(to: rule) { pointer in
            Attribute(body: pointer, value: nil) { R._update }
        }
    }
}

// TODO:
private struct AttributeType {
    var graphType: OGAttributeType
    var type: _AttributeBody.Type
}

@_silgen_name("OGGraphCreateAttribute")
@inline(__always)
@inlinable
func OGGraphCreateAttribute(index: Int, body: UnsafeRawPointer, value: UnsafeRawPointer?) -> OGAttribute

@_silgen_name("OGGraphGetValue")
@inline(__always)
@inlinable
func OGGraphGetValue<Value>(_ attribute: OGAttribute, options: OGValueOptions = [], type: Value.Type = Value.self) -> OGValue

@_silgen_name("OGGraphSetValue")
@inline(__always)
@inlinable
func OGGraphSetValue<Value>(_ attribute: OGAttribute, valuePointer: UnsafePointer<Value>) -> Bool
