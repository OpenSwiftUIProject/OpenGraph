//
//  DebugServer.swift
//
//
//  Created by Kyle on 2024/1/21.
//

#if canImport(Darwin)
@_silgen_name("OGDebugServerStart")
@inline(__always)
public func debugServerStart(_ port: UInt) -> UnsafeRawPointer?

@_silgen_name("OGDebugServerStop")
@inline(__always)
public func debugServerStop()

@_silgen_name("OGDebugServerCopyURL")
@inline(__always)
public func debugServerCopyURL() -> CFURL?

@_silgen_name("OGDebugServerRun")
@inline(__always)
public func debugServerRun(_ timeout: Int)
#endif
