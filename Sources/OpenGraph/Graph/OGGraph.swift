//
//  OGGraph.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

public import OpenGraph_SPI

extension OGGraph {
    public static func typeIndex(
        ctx: OGGraphContext,
        body: _AttributeBody.Type,
        valueType: Metadata,
        flags: OGAttributeTypeFlags,
        update: AttributeUpdateBlock
    ) -> Int {
        // TODO: __AGGraphInternAttributeType
        0
    }
}

extension OGGraph {
    @_silgen_name("OGGraphStartProfiling")
    public static func startProfiling(_ graph: OGGraph? = nil)

    @_silgen_name("OGGraphStopProfiling")
    public static func stopProfiling(_ graph: OGGraph? = nil)
}

// FIXME: migrate to use @_extern(c, "xx") in Swift 6
// > Also similar to @_silgen_name, but a function declared with @_extern(c) is assumed to use the C ABI, while @_silgen_name assumes the Swift ABI.
//extension OGGraph {
//    @_silgen_name("OGGGraphSetInvalidationCallback") // Use Swift ABI(self: x20) ❌, we need C ABI here(self: x0).
//    public func setInvalidationCallback(_ callback: ((AnyAttribute) -> Void)?)
//
//    @_silgen_name("OGGGraphSetUpdateCallback")
//    public func setUpdateCallback(_ callback: (() -> Void)?)
//}
extension OGGraph {
    @_silgen_name("OGGraphSetInvalidationCallback")
    public static func setInvalidationCallback(_ graph: OGGraph, callback: ((AnyAttribute) -> Void)?)

    @_silgen_name("OGGraphSetUpdateCallback")
    public static func setUpdateCallback(_ graph: OGGraph, callback: (() -> Void)?)
}

extension OGGraph {
    @_transparent
    @inline(__always)
    public var mainUpdates: Int { numericCast(counter(for: ._10)) }
}

extension OGGraph {
    public static func withoutUpdate<Value>(_ body: () -> Value) -> Value {
        let update = clearUpdate()
        defer { setUpdate(update) }
        return body()
    }
}

extension OGGraph {
    // NOTE: Currently Swift does not support generic computed variable
    @_silgen_name("OGGraphGetOutputValue")
    @inline(__always)
    @inlinable
    public static func outputValue<Value>() -> UnsafePointer<Value>?

    @_silgen_name("OGGraphSetOutputValue")
    @inline(__always)
    @inlinable
    public static func setOutputValue<Value>(_ value: UnsafePointer<Value>)
}
