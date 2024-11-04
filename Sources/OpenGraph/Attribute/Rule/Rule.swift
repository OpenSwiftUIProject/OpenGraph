//
//  _AttributeBody.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

import OpenGraph_SPI

public protocol Rule: _AttributeBody {
    associatedtype Value
    static var initialValue: Value? { get }
    var value: Value { get }
}

// MARK: - Rule Protocol default implementation

extension Rule {
    public static var initialValue: Value? { nil }

    public static func _update(_ pointer: UnsafeMutableRawPointer, attribute _: AnyAttribute) {
        let rule = pointer.assumingMemoryBound(to: Self.self)
        let value = rule.pointee.value
        // Verified for RELEASE_2023
        withUnsafePointer(to: value) { value in
            OGGraph.setOutputValue(value)
        }
    }

    public static func _updateDefault(_: UnsafeMutableRawPointer) {
        guard let initialValue else {
            return
        }
        // Verified for RELEASE_2023
        withUnsafePointer(to: initialValue) { value in
            OGGraph.setOutputValue(value)
        }
    }
}

// MARK: - Rule extension

extension Rule {
    public var attribute: Attribute<Value> {
        Attribute<Value>(identifier: AnyAttribute.current!)
    }

    public var context: RuleContext<Value> {
        RuleContext<Value>(attribute: attribute)
    }
}

// MARK: - Rule extension for Hashable Value

extension Rule where Self: Hashable {
    public func cachedValue(
        options: OGCachedValueOptions = [],
        owner: AnyAttribute?
    ) -> Value {
        withUnsafePointer(to: self) { pointer in
            Self._cachedValue(
                options: options,
                owner: owner,
                hashValue: hashValue,
                bodyPtr: pointer,
                update: { Self._update }
            ).pointee
        }
    }
    
    public func cachedValueIfExists(
        options: OGCachedValueOptions = [],
        owner: AnyAttribute?
    ) -> Value? {
        withUnsafePointer(to: self) { bodyPointer in
            let value = __OGGraphReadCachedAttributeIfExists(hashValue, OGTypeID(Self.self), bodyPointer, OGTypeID(Value.self), options, owner ?? .nil, false)
            guard let value else { return nil }
            return value.assumingMemoryBound(to: Value.self).pointee
        }
    }

    public static func _cachedValue(
        options: OGCachedValueOptions = [],
        owner: AnyAttribute?,
        hashValue: Int, 
        bodyPtr: UnsafeRawPointer, 
        update: AttributeUpdateBlock
    ) -> UnsafePointer<Value> {
        // TODO: pass closure here
        __OGGraphReadCachedAttribute(hashValue, OGTypeID(Self.self), bodyPtr, OGTypeID(Value.self), options, owner ?? .nil, false)
            .assumingMemoryBound(to: Value.self)
    }
}
