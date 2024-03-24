//
//  OGSubgraph.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

import _OpenGraph

extension OGSubgraph {
    public func addObserver(_ observer: () -> Void) -> Int {
        OGSubgraph.addObserver(self, observer: observer)
    }
    
    public func apply<Value>(_ body: () -> Value) -> Value {
        let update = OGGraph.clearUpdate()
        let current = OGSubgraph.current
        defer {
            OGSubgraph.current = current
            OGGraph.setUpdate(update)
        }
        return body()
    }
    
    public func forEach(_ flags: OGAttributeFlags, _ callback: (OGAttribute) -> Void) {
        OGSubgraph.apply(self, flags: flags, callback: callback)
    }
    
    /*public*/ static func beginTreeElement<A>(value _: Attribute<A>, flags _: UInt32) {
        fatalError("TODO")
    }
    
    /*public*/ static func addTreeValue<A>(_: Attribute<A>, forKey _: UnsafePointer<Int8>, flags _: UInt32) {
        fatalError("TODO")
    }
    
    /*public*/ static func endTreeElement<A>(value _: Attribute<A>) {
        fatalError("TODO")
    }
}

// FIXME: migrate to use @_extern(c, "xx") in Swift 6
extension OGSubgraph {
    @_silgen_name("OGSubgraphApply")
    private static func apply(_ graph: OGSubgraph, flags: OGAttributeFlags, callback: (OGAttribute) -> Void)
    
    @_silgen_name("OGSubgraphAddObserver")
    private static func addObserver(_ graph: OGSubgraph, observer: () -> Void) -> Int
}
