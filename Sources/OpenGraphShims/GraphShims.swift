//
//  GraphShims.swift
//
//
//  Created by Kyle on 2023/12/21.
//

#if OPENGRAPH_ATTRIBUTEGRAPH
@_exported import AttributeGraph
public typealias OGAttribute = AGAttribute
public typealias OGAttributeFlags = AGAttributeFlags
public typealias OGAttributeTypeFlags = AGAttributeTypeFlags
public typealias OGComparisonMode = AGComparisonMode
public typealias OGComparisonOptions = AGComparisonOptions
public typealias OGDebugServer = AGDebugServer
public typealias OGGraph = AGGraph
public typealias OGGraphContext = AGGraphContext
public typealias OGInputOptions = AGInputOptions
public typealias OGSearchOptions = AGSearchOptions
public typealias OGSubgraph = AGSubgraph
public typealias OGSwiftMetadata = AGSwiftMetadata
public typealias OGTupleType = AGTupleType
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGTypeKind = AGTypeKind
public typealias OGTypeID = AGTypeID
public typealias OGUniqueID = AGUniqueID
#else
@_exported import OpenGraph
#endif
