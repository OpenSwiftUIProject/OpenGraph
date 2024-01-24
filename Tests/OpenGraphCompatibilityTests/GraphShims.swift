//
//  GraphShims.swift
//
//
//  Created by Kyle on 2024/1/24.
//

#if OPENGRAPH_COMPATIBILITY_TEST
@_exported import AttributeGraph
public typealias OGAttribute = AGAttribute
public typealias OGUniqueID = AGUniqueID
public typealias OGSwiftMetadata = AGSwiftMetadata
public typealias OGTypeID = AGTypeID
public typealias OGTypeApplyOptions = AGTypeApplyOptions
#else
@_exported import OpenGraph
#endif
