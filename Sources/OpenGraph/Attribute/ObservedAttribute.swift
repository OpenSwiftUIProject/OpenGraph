//
//  ObservedAttribute.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/25.
//  Lastest Version: iOS 15.5
//  Status: Complete

public protocol ObservedAttribute: _AttributeBody {
    func destroy()
}

extension ObservedAttribute {
    public static func _destroySelf(_ pointer: UnsafeMutableRawPointer) {
        pointer.assumingMemoryBound(to: Self.self).pointee.destroy()
    }
    
    public static var _hasDestroySelf: Bool {
        true
    }
}
