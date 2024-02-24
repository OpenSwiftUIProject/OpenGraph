import _OpenGraph

@frozen
public struct RuleContext<Value> {
    public var attribute: Attribute<Value>

    public init(attribute: Attribute<Value>) {
        self.attribute = attribute
    }
    
    public var value: Value {
        unsafeAddress {
            OGGraphGetOutputValue()!
        }
        nonmutating set {
            withUnsafePointer(to: newValue) { valuePointer in
                OGGraphSetOutputValue(valuePointer)
            }
        }
    }
    
    public var hasValue: Bool {
        let valuePointer: UnsafePointer<Value>? = OGGraphGetOutputValue()
        return valuePointer != nil
    }
}
