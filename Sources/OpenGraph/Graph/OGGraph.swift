//
//  OGGraph.swift
//
//
//  Created by Kyle on 2024/1/18.
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
