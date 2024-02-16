//
//  _AttributeBody.swift
//  OpenGraph
//
//  Updated by Kyle on 2024/2/16.'
//  Lastest Version: iOS 15.5
//  Status: Blocked by AttributeBodyVisitor

import _OpenGraph

public protocol _AttributeBody {
    static func _destroySelf(_ value: UnsafeMutableRawPointer)
    static var _hasDestroySelf: Bool { get }
    static func _updateDefault(_ value: UnsafeMutableRawPointer)
    static var comparisonMode: OGComparisonMode { get }
    static var flags: OGAttributeTypeFlags { get }
}

// MARK: - Protocol Default implementation

extension _AttributeBody {
    public static func _destroySelf(_ value: UnsafeMutableRawPointer) {}
    public static var _hasDestroySelf: Bool { false }
    public static func _updateDefault(_ value: UnsafeMutableRawPointer) {}
    public static var comparisonMode: OGComparisonMode { ._2 }
    public static var flags: OGAttributeTypeFlags { ._8 }
}

extension _AttributeBody {
    static func _visitBody<Visitor: AttributeBodyVisitor>(_ visitor: inout Visitor, _ body: UnsafeRawPointer) {
        visitor.visit(body: body.assumingMemoryBound(to: Self.self))
    }
}
