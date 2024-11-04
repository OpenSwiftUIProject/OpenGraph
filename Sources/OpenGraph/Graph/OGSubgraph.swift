//
//  OGSubgraph.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

import OpenGraph_SPI

extension OGSubgraph {
    public func addObserver(_ observer: () -> Void) -> Int {
        OGSubgraph.addObserver(self, observer: observer)
    }
    
    public func apply<Value>(_ body: () -> Value) -> Value {
        #if !os(WASI)
        let update = OGGraph.clearUpdate()
        let current = OGSubgraph.current
        defer {
            OGSubgraph.current = current
            OGGraph.setUpdate(update)
        }
        OGSubgraph.current = self
        return body()
        #else
        fatalError("upstream SIL Compiler assert issue")
        #endif
    }
    
    public func forEach(_ flags: OGAttributeFlags, _ callback: (AnyAttribute) -> Void) {
        OGSubgraph.apply(self, flags: flags, callback: callback)
    }
}

extension OGSubgraph {
    public static func beginTreeElement<Value>(value: Attribute<Value>, flags: UInt32) {
        if shouldRecordTree {
            __OGSubgraphBeginTreeElement(value.identifier, OGTypeID(Value.self), flags)
        }
    }
    
    public static func addTreeValue<Value>(_ value: Attribute<Value>, forKey key: UnsafePointer<Int8>, flags: UInt32) {
        if shouldRecordTree {
            __OGSubgraphAddTreeValue(value.identifier, OGTypeID(Value.self), key, flags)
        }
    }
    
    public static func endTreeElement<Value>(value: Attribute<Value>) {
        if shouldRecordTree {
            __OGSubgraphEndTreeElement(value.identifier)
        }
    }
}

// FIXME: migrate to use @_extern(c, "xx") in Swift 6
extension OGSubgraph {
    @_silgen_name("OGSubgraphApply")
    private static func apply(_ graph: OGSubgraph, flags: OGAttributeFlags, callback: (AnyAttribute) -> Void)
    
    @_silgen_name("OGSubgraphAddObserver")
    private static func addObserver(_ graph: OGSubgraph, observer: () -> Void) -> Int
}
