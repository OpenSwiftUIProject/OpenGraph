import _OpenGraph

@propertyWrapper
public struct Attribute<Value> {
    public var identifier: OGAttribute
    
    public init() {
        fatalError("TODO")
    }

    public var wrappedValue: Value { fatalError() }

    @inlinable
    public subscript<Member>(keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        fatalError()
    }
    
    public var value: Value {
        get { wrappedValue }
        set { fatalError("TODO") }
    }
    
    @inlinable
    public func addInput(_ attribute: OGAttribute, options: OGInputOptions, token: Int) {
        __OGGraphAddInput(self.identifier, attribute, options, token)
    }
    
    @inlinable
    public func addInput<V>(_ attribute: Attribute<V>, options: OGInputOptions, token: Int) {
        addInput(attribute.identifier, options: options, token: token)
    }
}

extension Attribute: Equatable {}
