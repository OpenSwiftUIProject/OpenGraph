//
//  TreeElement.swift
//  OpenGraph

public import OpenGraphCxx

extension TreeElement {
    public var value: AnyAttribute? {
        let result = __OGTreeElementGetValue(self)
        return result == .nil ? nil : result
    }
}

extension Nodes: @retroactive IteratorProtocol {
    public typealias Element = AnyAttribute
    public mutating func next() -> AnyAttribute? {
        let result = __OGTreeElementGetNextNode(&self)
        return result == .nil ? nil : result
    }
}

extension Children: @retroactive IteratorProtocol {
    public typealias Element = TreeElement
}

extension Values: @retroactive IteratorProtocol {
    public typealias Element = TreeValue
}

extension TreeElement {
    public struct LocalChildren {
        public var base: Children
    }
}
