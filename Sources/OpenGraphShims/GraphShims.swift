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
public typealias OGSwiftMetadata = AGSwiftMetadata
public typealias OGTypeID = AGTypeID
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGTupleType = AGTupleType
public typealias OGGraph = AGGraph
public typealias OGSubgraph = AGSubgraph
#else
@_exported import OpenGraph
#endif
