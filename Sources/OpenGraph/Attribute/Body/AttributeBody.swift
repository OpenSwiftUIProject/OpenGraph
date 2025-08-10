//
//  _AttributeBody.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

public import OpenGraphCxx

public protocol _AttributeBody {
    static func _destroySelf(_ pointer: UnsafeMutableRawPointer)
    static var _hasDestroySelf: Bool { get }
    static func _updateDefault(_ pointer: UnsafeMutableRawPointer)
    static var comparisonMode: ComparisonMode { get }
    static var flags: _AttributeType.Flags { get }
}

// MARK: - Protocol Default implementation

extension _AttributeBody {
    public static func _destroySelf(_ pointer: UnsafeMutableRawPointer) {}
    public static var _hasDestroySelf: Bool { false }
    public static func _updateDefault(_ pointer: UnsafeMutableRawPointer) {}
    public static var comparisonMode: ComparisonMode { .equatableUnlessPOD }
    public static var flags: _AttributeType.Flags { .mainThread }
}

extension _AttributeBody {
    static func _visitBody<Visitor: AttributeBodyVisitor>(_ visitor: inout Visitor, _ body: UnsafeRawPointer) {
        visitor.visit(body: body.assumingMemoryBound(to: Self.self))
    }
}
