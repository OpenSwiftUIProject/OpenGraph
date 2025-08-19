//
//  Attribute+Debug.swift
//  OpenGraphShims

extension Attribute: Swift.CustomDebugStringConvertible {
    public var debugDescription: String {
        #"""
        Attribute<\#(Value.self)> {
        \#(identifier.debugDescription)
        }
        """#
    }
}

extension AnyAttribute: Swift.CustomDebugStringConvertible {
    public var debugDescription: String {
        guard self != .nil else {
            return "AnyAttribute.nil"
        }
        var description = #"""
        rawValue: \#(rawValue)
        graph: \#(graph)
        """#
        if rawValue % 2 == 0 { // direct
            description.append("\n(direct attribute)")

            let valueType = valueType
            description.append("\nvalueType: \(valueType)")

            var value: Any!
            func project1<T>(type: T.Type) {
                value = unsafeCast(to: type).value
            }
            _openExistential(valueType, do: project1)
            description.append("\nvalue: \(value!)")

            let bodyType = _bodyType
            description.append("\nbodyType: \(bodyType)")

            var bodyValue: Any!
            func project2<T>(type: T.Type) {
                bodyValue = _bodyPointer.assumingMemoryBound(to: type).pointee
            }
            _openExistential(bodyType, do: project2)
            description.append("\nbodyValue: \(bodyValue!)")

        } else { // indrect
            description.append("\n(indirect attribute)")
            description.append("\n\nsource attribute:")
            description.append("\n\(source.debugDescription)")
        }
        return description
    }
}
