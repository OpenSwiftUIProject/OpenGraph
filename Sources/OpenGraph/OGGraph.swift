//
//  OGGraph.swift
//
//
//  Created by Kyle on 2024/1/18.
//

import _OpenGraph
import Foundation

@_silgen_name("OGGraphArchiveJSON")
@inline(__always)
public func graphArchiveJSON(_ name: UnsafePointer<Int8>)

@_silgen_name("OGGraphCreate")
@inline(__always)
public func graphCreate() -> UnsafeRawPointer?

@_silgen_name("OGGraphCreateShared")
@inline(__always)
public func graphCreateShared(_: UnsafeRawPointer?) -> UnsafeRawPointer?

#if canImport(ObjectiveC)
@_silgen_name("OGGraphDescription")
@inline(__always)
public func graphDescription(_ graph: UnsafeRawPointer? = nil, options: NSDictionary) -> UnsafeRawPointer?
#endif
