//
//  GraphShims.swift
//  OpenGraphShims

#if OPENGRAPH_ATTRIBUTEGRAPH
@_exported public import AttributeGraph
public typealias OGAttributeInfo = AGAttributeInfo
public typealias OGAttributeType = AGAttributeType
public typealias OGCachedValueOptions = AGCachedValueOptions
public typealias OGChangedValueFlags = AGChangedValueFlags
public typealias OGCounterQueryType = AGCounterQueryType
public typealias OGInputOptions = AGInputOptions
public typealias OGTypeApplyOptions = AGTypeApplyOptions
public typealias OGUniqueID = AGUniqueID
public typealias OGValue = AGValue
public typealias OGValueOptions = AGValueOptions
public typealias OGValueState = AGValueState
public let attributeGraphEnabled = true
public let swiftToolchainSupported = true
#else
@_exported import OpenGraph
public let attributeGraphEnabled = false
#if OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED
public let swiftToolchainSupported = true
#else
public let swiftToolchainSupported = false
#endif
#endif
