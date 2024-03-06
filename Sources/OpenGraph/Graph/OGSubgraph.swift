//
//  OGSubgraph.swift
//
//
//

import _OpenGraph

extension OGSubgraph {
    func addObserver(_: () -> Void) -> Int {
        fatalError("TODO")
    }
    
    func apply<A>(_: () -> A) -> A {
        fatalError("TODO")
    }
    
    func forEach(_: OGAttributeFlags, _: (OGAttribute) -> Void) {
        fatalError("TODO")
    }
    
    static func beginTreeElement<A>(value _: Attribute<A>, flags _: UInt32) {
        fatalError("TODO")
    }
    
    static func addTreeValue<A>(_: Attribute<A>, forKey _: UnsafePointer<Int8>, flags _: UInt32) {
        fatalError("TODO")
    }
    
    static func endTreeElement<A>(value _: Attribute<A>) {
        fatalError("TODO")
    }
}

// TODO: migrate to use @_extern(c, "xx") in Swift 6
extension OGSubgraph {
    @_silgen_name("OGSubgraphApply")
    public static func apply(_ graph: OGSubgraph, flags: OGAttributeFlags, callback: @escaping (OGAttribute) -> Void)
}
