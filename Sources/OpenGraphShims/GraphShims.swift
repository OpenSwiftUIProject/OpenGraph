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
#else
@_exported import OpenGraph
#endif
