//
//  GraphShims.swift
//
//
//

#if OPENGRAPH_ATTRIBUTEGRAPH
@_exported import AttributeGraph
public typealias OGAttribute = AGAttribute
public typealias OGAttributeFlags = AGAttributeFlags
public typealias OGAttributeInfo = AGAttributeInfo
public typealias OGAttributeType = AGAttributeType
public typealias OGAttributeTypeFlags = AGAttributeTypeFlags
public typealias OGCachedValueOptions = AGCachedValueOptions
public typealias OGChangedValueFlags = AGChangedValueFlags
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
public typealias OGValue = AGValue
public typealias OGValueOptions = AGValueOptions
public typealias OGValueState = AGValueState
public typealias OGWeakAttribute = AGWeakAttribute
public let attributeGraphEnabled = true
#else
@_exported import OpenGraph
public let attributeGraphEnabled = false
#endif
