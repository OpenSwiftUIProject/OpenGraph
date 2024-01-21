import _OpenGraph

@propertyWrapper
public struct Attribute<Value> {
    #if canImport(Darwin)
    // FIXME: Linux compiler will crash here
    var identifier: OGAttribute
    #endif
    
    public init() {
        fatalError("TODO")
    }

    public var wrappedValue: Value { fatalError() }

    @inlinable
    public subscript<Member>(keyPath: KeyPath<Value, Member>) -> Attribute<Member> {
        fatalError()
    }
}

extension Attribute: Equatable {}
