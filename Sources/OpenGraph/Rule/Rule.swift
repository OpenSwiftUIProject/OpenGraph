//
//  _AttributeBody.swift
//  OpenGraph
//
//  Updated by Kyle on 2024/2/24.
//  Lastest Version: iOS 15.5
//  Status: Complete

import _OpenGraph

public protocol Rule: _AttributeBody {
    associatedtype Value
    static var initialValue: Value? { get }
    var value: Value { get }
}

// MARK: - Rule Protocol default implementation

extension Rule {
    public static var initialValue: Value? { nil }

    public static func _update(_ pointer: UnsafeMutableRawPointer, attribute _: OGAttribute) {
        let rule = pointer.assumingMemoryBound(to: Self.self)
        let value = rule.pointee.value
        // Verified for iOS 17
        withUnsafePointer(to: value) { valuePointer in
            __OGGraphSetOutputValue(valuePointer, OGTypeID(Value.self))
        }
    }

    public static func _updateDefault(_: UnsafeMutableRawPointer) {
        guard let initialValue else {
            return
        }
        // Verified for iOS 17
        withUnsafePointer(to: initialValue) { valuePointer in
            __OGGraphSetOutputValue(valuePointer, OGTypeID(Value.self))
        }
    }
}

// MARK: - Rule extension

extension Rule {
    public var attribute: Attribute<Value> {
        Attribute<Value>(identifier: OGAttribute.current!)
    }

    public var context: RuleContext<Value> {
        RuleContext<Value>(attribute: attribute)
    }
}

// MARK: - Rule extension for Hashable Value

extension Rule where Value: Hashable {
    public func cachedValueIfExists(
        options: OGCachedValueOptions,
        owner: OGAttribute?
    ) -> Value? {
        fatalError("TODO")
    }
    
    public func cachedValue(
        options: OGCachedValueOptions,
        owner: OGAttribute?
    ) -> Value {
        withUnsafePointer(to: self) { pointer in
            Self._cachedValue(
                options: options,
                owner: owner,
                hashValue: value.hashValue,
                bodyPtr: pointer
            ) {
                fatalError("TODO")
            }.pointee
        }
    }

    public static func _cachedValue(
        options: OGCachedValueOptions,
        owner: OGAttribute?,
        hashValue: Int, 
        bodyPtr: UnsafeRawPointer, 
        update: () -> (UnsafeMutableRawPointer, OGAttribute) -> ()
    ) -> UnsafePointer<Value> {
        fatalError("TODO")
    }
}
