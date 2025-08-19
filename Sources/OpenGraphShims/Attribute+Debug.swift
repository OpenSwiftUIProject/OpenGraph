//
//  Attribute+Debug.swift
//  OpenGraphShims

#if canImport(Darwin) && DEBUG // Compiler crash for Darwin + release and non-Darwin build

// Use 4 spaces instead of \t for bettern test case expect
private let tab = "    "

extension Attribute: Swift.CustomDebugStringConvertible {
    public var debugDescription: String {
        _debugDescription(indent: 0)
    }
    
    func _debugDescription(indent: Int) -> String {
        let tabs = String(repeating: tab, count: indent)
        return #"""
        \#(tabs)Attribute<\#(Value.self)> {
        \#(identifier._debugDescription(indent: indent + 1))
        \#(tabs)}
        """#
    }
}

extension AnyAttribute: Swift.CustomDebugStringConvertible {
    public var debugDescription: String {
        _debugDescription(indent: 0)
    }
    
    func _debugDescription(indent: Int) -> String {
        let tabs = String(repeating: tab, count: indent)

        guard self != .nil else {
            return "\(tabs)AnyAttribute.nil"
        }
        
        var description = #"""
        \#(tabs)rawValue: \#(rawValue)
        \#(tabs)graph: \#(graph)
        """#
        
        if rawValue % 2 == 0 { // direct
            description.append("\n\(tabs)(direct attribute)")

            let valueType = valueType
            description.append("\n\(tabs)valueType: \(valueType)")

            var value: Any!
            func project1<T>(type: T.Type) {
                value = unsafeCast(to: type).value
            }
            _openExistential(valueType, do: project1)
            description.append("\n\(tabs)value: \(value!)")

            let bodyType = _bodyType
            description.append("\n\(tabs)bodyType: \(bodyType)")

            var bodyValue: Any!
            func project2<T>(type: T.Type) {
                bodyValue = _bodyPointer.assumingMemoryBound(to: type).pointee
            }
            _openExistential(bodyType, do: project2)
            
            let bodyValueDescription = _formatBodyValue(bodyValue!, indent: indent)
            description.append("\n\(tabs)bodyValue:\n\(bodyValueDescription)")

        } else { // indirect
            description.append("\n\(tabs)(indirect attribute)")
            description.append("\n\(tabs)source attribute:")
            description.append("\n\(source._debugDescription(indent: indent + 1))")
        }
        return description
    }
    
    private func _formatBodyValue(_ bodyValue: Any, indent: Int) -> String {
        let bodyValueString = String(describing: bodyValue)
        let nextTabs = String(repeating: tab, count: indent + 1)

        // Check if the body value contains attributes
        if bodyValueString.contains("Attribute<") {
            // Split lines and add proper indentation
            let lines = bodyValueString.components(separatedBy: .newlines)
            return lines.enumerated().map { index, line in
                return "\(nextTabs)\(line)"
            }.joined(separator: "\n")
        }
        
        return "\(nextTabs)\(bodyValueString)"
    }
}
#endif
