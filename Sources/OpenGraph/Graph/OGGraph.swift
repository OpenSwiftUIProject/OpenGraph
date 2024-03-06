//
//  OGGraph.swift
//
//
//

import _OpenGraph

extension OGGraph {
    public static func typeIndex(
        ctx: OGGraphContext,
        body: _AttributeBody.Type,
        valueType: OGTypeID,
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

// TODO: Update to use @_extern(c, "xx") after we migrate to Swift 6.0
// > Also similar to @_silgen_name, but a function declared with @_extern(c) is assumed to use the C ABI, while @_silgen_name assumes the Swift ABI.
//extension OGGraph {
//    @_silgen_name("OGGGraphSetInvalidationCallback") // Use Swift ABI(self: x20) ❌, we need C ABI here(self: x0).
//    public func setInvalidationCallback(_ callback: ((OGAttribute) -> Void)?)
//    
//    @_silgen_name("OGGGraphSetUpdateCallback")
//    public func setUpdateCallback(_ callback: (() -> Void)?)
//}

extension OGGraph {
    @_silgen_name("OGGraphSetInvalidationCallback")
    public static func setInvalidationCallback(_ graph: OGGraph, callback: ((OGAttribute) -> Void)?)

    @_silgen_name("OGGraphSetUpdateCallback")
    public static func setUpdateCallback(_ graph: OGGraph, callback: (() -> Void)?)
}
