//
//  RuleContext.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

public import OpenGraphCxx

@frozen
public struct RuleContext<Value>: Equatable {
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
    
    public subscript<V>(weakAttribute: WeakAttribute<V>) -> V? {
        weakAttribute.attribute.map { attribute in
            OGGraphGetInputValue(self.attribute.identifier, input: attribute.identifier, type: V.self)
                .value
                .assumingMemoryBound(to: V.self)
                .pointee
        }
    }

    public subscript<V>(optionalAttribute: OptionalAttribute<V>) -> V? {
        optionalAttribute.attribute.map { attribute in
            OGGraphGetInputValue(self.attribute.identifier, input: attribute.identifier, type: V.self)
                .value
                .assumingMemoryBound(to: V.self)
                .pointee
        }
    }

    public var value: Value {
        unsafeAddress {
            Graph.outputValue()!
        }
        nonmutating set {
            withUnsafePointer(to: newValue) { value in
                Graph.setOutputValue(value)
            }
        }
    }
    
    public var hasValue: Bool {
        let valuePointer: UnsafePointer<Value>? = Graph.outputValue()
        return valuePointer != nil
    }
        
    public func valueAndFlags<V>(of input: Attribute<V>, options: OGValueOptions = []) -> (value: V, flags: OGChangedValueFlags) {
        let value = OGGraphGetInputValue(attribute.identifier, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.flags
        )
    }
    
    public func changedValue<V>(of input: Attribute<V>, options: OGValueOptions = []) -> (value: V, changed: Bool) {
        let value = OGGraphGetInputValue(attribute.identifier, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.flags.contains(.changed)
        )
    }
    
    public func update(body: () -> Void) {
        OGGraphWithUpdate(attribute.identifier, body: body)
    }
}

@_silgen_name("OGGraphGetInputValue")
@inline(__always)
@inlinable
func OGGraphGetInputValue<Value>(_ attribute: AnyAttribute, input: AnyAttribute, options: OGValueOptions = [], type: Value.Type = Value.self) -> OGValue

@_silgen_name("OGGraphWithUpdate")
@inline(__always)
@inlinable
func OGGraphWithUpdate(_ attribute: AnyAttribute, body: () -> Void)
