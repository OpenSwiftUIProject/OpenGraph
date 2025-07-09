//
//  GraphShims.swift
//  OpenGraphShims

#if OPENGRAPH_ATTRIBUTEGRAPH
@_exported public import AttributeGraph
public typealias OGAttributeFlags = AGAttributeFlags
public typealias OGAttributeInfo = AGAttributeInfo
public typealias OGAttributeType = AGAttributeType
public typealias OGAttributeTypeFlags = AGAttributeTypeFlags
public typealias OGCachedValueOptions = AGCachedValueOptions
public typealias OGChangedValueFlags = AGChangedValueFlags
public typealias OGComparisonMode = AGComparisonMode
public typealias OGComparisonOptions = AGComparisonOptions
public typealias OGCounterQueryType = AGCounterQueryType
public typealias OGDebugServer = AGDebugServer
public typealias OGInputOptions = AGInputOptions
public typealias OGSearchOptions = AGSearchOptions
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGUniqueID = AGUniqueID
public typealias OGValue = AGValue
public typealias OGValueOptions = AGValueOptions
public typealias OGValueState = AGValueState
public let attributeGraphEnabled = true
public let swiftToolchainSupported = true
#elseif OPENGRAPH_COMPUTE
@_exported import Compute
//typealias Graph = AGGraph
#else
@_exported import OpenGraph
public let attributeGraphEnabled = false
#if OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
public let swiftToolchainSupported = true
#else
public let swiftToolchainSupported = false
#endif
#endif
