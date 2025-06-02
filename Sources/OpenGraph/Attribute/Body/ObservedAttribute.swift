//
//  ObservedAttribute.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

public protocol ObservedAttribute: _AttributeBody {
    mutating func destroy()
}

extension ObservedAttribute {
    public static func _destroySelf(_ pointer: UnsafeMutableRawPointer) {
        pointer.assumingMemoryBound(to: Self.self).pointee.destroy()
    }
    
    public static var _hasDestroySelf: Bool {
        true
    }
}
