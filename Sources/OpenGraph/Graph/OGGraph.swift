//
//  OGGraph.swift
//
//
//  Created by Kyle on 2024/1/18.
//

import _OpenGraph

@_silgen_name("OGGraphArchiveJSON")
@inline(__always)
public func graphArchiveJSON(_ name: UnsafePointer<Int8>)

#if canImport(ObjectiveC)
import Foundation

@_silgen_name("OGGraphDescription")
@inline(__always)
public func graphDescription(_ graph: OGGraph? = nil, options: CFDictionary) -> UnsafeRawPointer?
#endif
