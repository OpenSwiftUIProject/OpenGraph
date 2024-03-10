//
//  RuleContext.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Blocked by WeakAttribute and OptionalAttribute

import _OpenGraph

@frozen
public struct RuleContext<Value> {
    public var attribute: Attribute<Value>

    public init(attribute: Attribute<Value>) {
        self.attribute = attribute
    }
    
    public subscript<V>(attribute: Attribute<V>) -> V {
        unsafeAddress {
            OGGraphGetInputValue(self.attribute.identifier, input: attribute.identifier, type: V.self)
                .value
                .assumingMemoryBound(to: V.self)
        }
    }
    
//    public subscript<V>(weakAttribute: WeakAttribute<V>) -> V? {
//        get
//    }
//
//    public subscript<V>(optionalAttribute: OptionalAttribute<V>) -> V? {
//        get
//    }
//
    public var value: Value {
        unsafeAddress {
            OGGraphGetOutputValue()!
        }
        nonmutating set {
            withUnsafePointer(to: newValue) { valuePointer in
                OGGraphSetOutputValue(valuePointer)
            }
        }
    }
    
    public var hasValue: Bool {
        let valuePointer: UnsafePointer<Value>? = OGGraphGetOutputValue()
        return valuePointer != nil
    }
        
    public func valueAndFlags<V>(of input: Attribute<V>, options: OGValueOptions = []) -> (value: V, flags: OGChangedValueFlags) {
        let value = OGGraphGetInputValue(attribute.identifier, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.changed ? ._1 : []
        )
    }
    
    public func changedValue<V>(of input: Attribute<V>, options: OGValueOptions = []) -> (value: V, changed: Bool) {
        let value = OGGraphGetInputValue(attribute.identifier, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.changed
        )
    }
    
    public func update(body: () -> Void) {
        OGGraphWithUpdate(attribute.identifier, body: body)
    }
}

@_silgen_name("OGGraphGetInputValue")
@inline(__always)
@inlinable
func OGGraphGetInputValue<Value>(_ attribute: OGAttribute, input: OGAttribute, options: OGValueOptions = [], type: Value.Type = Value.self) -> OGValue

@_silgen_name("OGGraphWithUpdate")
@inline(__always)
@inlinable
func OGGraphWithUpdate(_ attribute: OGAttribute, body: () -> Void)
