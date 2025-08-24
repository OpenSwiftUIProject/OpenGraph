//
//  Metadata.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

public import OpenGraphCxx
#if canImport(ObjectiveC)
public import Foundation
#endif

@_silgen_name("OGTypeApplyFields")
public func OGTypeApplyFields(
    _ type: Any.Type,
    body: (UnsafePointer<Int8>, Int, Any.Type) -> Void
)

@_silgen_name("OGTypeApplyFields2")
public func OGTypeApplyFields2(
    _ type: Any.Type,
    options: OGTypeApplyOptions,
    body: (UnsafePointer<Int8>, Int, Any.Type) -> Bool
) -> Bool

extension Metadata: Swift.Hashable, Swift.CustomStringConvertible {
    @inlinable
    @inline(__always)
    public init(_ type: any Any.Type) {
        self.init(rawValue: unsafeBitCast(type, to: UnsafePointer<_Metadata>.self))
    }
    
    @inlinable
    @inline(__always)
    public var type: any Any.Type {
        unsafeBitCast(rawValue, to: Any.Type.self)
    }
    
    @inlinable
    @inline(__always)
    public var description: String {
        #if canImport(ObjectiveC)
        __OGTypeDescription(self) as NSString as String
        #else
        fatalError("Unimplemented")
        #endif
    }
    
    @inlinable
    @inline(__always)
    /* public */func forEachField(
        do body: (UnsafePointer<Int8>, Int, Any.Type) -> Void
    ) {
        OGTypeApplyFields(type, body: body)
    }
    
    @inlinable
    @inline(__always)
    public func forEachField(
        options: OGTypeApplyOptions,
        do body: (UnsafePointer<Int8>, Int, Any.Type) -> Bool
    ) -> Bool {
        OGTypeApplyFields2(type, options: options, body: body)
    }
}

extension Signature: @retroactive Equatable {

    public static func == (_ lhs: Signature, _ rhs: Signature) -> Bool {
        return lhs.bytes.0 == rhs.bytes.0 && lhs.bytes.1 == rhs.bytes.1
            && lhs.bytes.2 == rhs.bytes.2 && lhs.bytes.3 == rhs.bytes.3
            && lhs.bytes.4 == rhs.bytes.4 && lhs.bytes.5 == rhs.bytes.5
            && lhs.bytes.6 == rhs.bytes.6 && lhs.bytes.7 == rhs.bytes.7
            && lhs.bytes.8 == rhs.bytes.8 && lhs.bytes.9 == rhs.bytes.9
            && lhs.bytes.10 == rhs.bytes.10 && lhs.bytes.11 == rhs.bytes.11
            && lhs.bytes.12 == rhs.bytes.12 && lhs.bytes.13 == rhs.bytes.13
            && lhs.bytes.14 == rhs.bytes.14 && lhs.bytes.15 == rhs.bytes.15
            && lhs.bytes.16 == rhs.bytes.16 && lhs.bytes.17 == rhs.bytes.17
            && lhs.bytes.18 == rhs.bytes.18 && lhs.bytes.19 == rhs.bytes.19
    }

}
