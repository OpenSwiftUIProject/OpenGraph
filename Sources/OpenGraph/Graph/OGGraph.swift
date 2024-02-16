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

@_silgen_name("OGGraphCreate")
@inline(__always)
public func graphCreate() -> OGGraph

@_silgen_name("OGGraphCreateShared")
@inline(__always)
public func graphCreateShared(_ graph: OGGraph? = nil) -> OGGraph

#if canImport(ObjectiveC)
import Foundation

@_silgen_name("OGGraphDescription")
@inline(__always)
public func graphDescription(_ graph: OGGraph? = nil, options: CFDictionary) -> UnsafeRawPointer?
#endif
