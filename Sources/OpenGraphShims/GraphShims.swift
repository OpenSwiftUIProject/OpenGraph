//
//  GraphShims.swift
//
//
//  Created by Kyle on 2023/12/21.
//

#if OPENGRAPH_ATTRIBUTEGRAPH
@_exported import AttributeGraph
public typealias OGAttribute = AGAttribute
public typealias OGUniqueID = AGUniqueID
#else
@_exported import OpenGraph
#endif

@_transparent
@inline(__always)
public func makeUniqueID() -> OGUniqueID {
    #if OPENGRAPH_ATTRIBUTEGRAPH
    AGMakeUniqueID()
    #else
    OGMakeUniqueID()
    #endif
}
