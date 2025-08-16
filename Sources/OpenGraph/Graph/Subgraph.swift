//
//  Subgraph.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

public import OpenGraphCxx

extension Subgraph {
    public typealias Flags = AnyAttribute.Flags

    // FIXME
    public typealias ChildFlags = AnyAttribute.Flags
}

extension Subgraph {
    public func addObserver(_ observer: () -> Void) -> Int {
        Subgraph.addObserver(self, observer: observer)
    }
    
    public func apply<Value>(_ body: () -> Value) -> Value {
        #if !os(WASI)
        let update = Graph.clearUpdate()
        let current = Subgraph.current
        defer {
            Subgraph.current = current
            Graph.setUpdate(update)
        }
        Subgraph.current = self
        return body()
        #else
        fatalError("upstream SIL Compiler assert issue")
        #endif
    }
    
    public func forEach(_ flags: Flags, _ callback: (AnyAttribute) -> Void) {
        Subgraph.apply(self, flags: flags, callback: callback)
    }
}

extension Subgraph {
    public static func beginTreeElement<Value>(value: Attribute<Value>, flags: UInt32) {
        if shouldRecordTree {
            __OGSubgraphBeginTreeElement(value.identifier, Metadata(Value.self), flags)
        }
    }
    
    public static func addTreeValue<Value>(_ value: Attribute<Value>, forKey key: UnsafePointer<Int8>, flags: UInt32) {
        if shouldRecordTree {
            __OGSubgraphAddTreeValue(value.identifier, Metadata(Value.self), key, flags)
        }
    }
    
    public static func endTreeElement<Value>(value: Attribute<Value>) {
        if shouldRecordTree {
            __OGSubgraphEndTreeElement(value.identifier)
        }
    }
}

// FIXME: migrate to use @_extern(c, "xx") in Swift 6
extension Subgraph {
    @_silgen_name("OGSubgraphApply")
    private static func apply(_ graph: Subgraph, flags: Flags, callback: (AnyAttribute) -> Void)
    
    @_silgen_name("OGSubgraphAddObserver")
    private static func addObserver(_ graph: Subgraph, observer: () -> Void) -> Int
}
