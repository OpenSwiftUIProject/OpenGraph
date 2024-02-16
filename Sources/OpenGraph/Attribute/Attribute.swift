import _OpenGraph

@propertyWrapper
public struct Attribute<Value> {
    var identifier: OGAttribute
    
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
}

extension Attribute: Equatable {}
