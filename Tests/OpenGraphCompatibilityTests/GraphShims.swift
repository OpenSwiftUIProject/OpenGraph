//
//  GraphShims.swift
//
//
//  Created by Kyle on 2024/1/24.
//

#if OPENGRAPH_COMPATIBILITY_TEST
@_exported import AttributeGraph
public typealias OGAttribute = AGAttribute
public typealias OGDebugServer = AGDebugServer
public typealias OGGraph = AGGraph
public typealias OGSubgraph = AGSubgraph
public typealias OGSwiftMetadata = AGSwiftMetadata
public typealias OGTupleType = AGTupleType
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGTypeID = AGTypeID
public typealias OGUniqueID = AGUniqueID
#else
@_exported import OpenGraph
#endif
