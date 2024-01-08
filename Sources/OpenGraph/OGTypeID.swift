//
//  OGTypeID.swift
//  OpenGraph
//
//  Created by Kyle on 2024/1/9.
//  Lastest Version: iOS 15.5
//  Status: WIP

import _OpenGraph

extension OGTypeID {
    public init(_ type: Any.Type) {
        self.init(rawValue: unsafeBitCast(type, to: UnsafePointer<OGSwiftMetadata>.self))
    }
    
    public var type: Any.Type {
        unsafeBitCast(rawValue, to: Any.Type.self)
    }
}
