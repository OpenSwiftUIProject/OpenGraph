//
//  GraphShims.swift
//  OpenGraphCompatibilityTests

#if OPENGRAPH_COMPATIBILITY_TEST
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
public typealias OGGraph = AGGraph
public typealias OGGraphContext = AGGraphContext
public typealias OGInputOptions = AGInputOptions
public typealias OGSearchOptions = AGSearchOptions
public typealias OGSubgraph = AGSubgraph
public typealias OGSwiftMetadata = AGSwiftMetadata
public typealias OGTupleType = AGTupleType
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGTypeKind = AGTypeKind
public typealias OGUniqueID = AGUniqueID
public typealias OGValue = AGValue
public typealias OGValueOptions = AGValueOptions
public typealias OGValueState = AGValueState
public let compatibilityTestEnabled = true
public let swiftToolchainSupported = true
#else
@_exported import OpenGraph
let compatibilityTestEnabled = false
#if OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
public let swiftToolchainSupported = true
#else
public let swiftToolchainSupported = false
#endif
#endif
