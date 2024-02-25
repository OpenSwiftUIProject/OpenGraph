//
//  AnyRuleContext.swift
//  OpenGraph
//
//  Updated by Kyle on 2024/2/25.
//  Lastest Version: iOS 15.5
//  Status: Blocked by WeakAttribute and OptionalAttribute

import _OpenGraph

@frozen
public struct AnyRuleContext {
    public var attribute: OGAttribute
    
    public init(attribute: OGAttribute) {
        self.attribute = attribute
    }
    
    public init<V>(_ context: RuleContext<V>) {
        attribute = context.attribute.identifier
    }
    
    public subscript<V>(attribute: Attribute<V>) -> V {
        unsafeAddress {
            OGGraphGetInputValue(self.attribute, input: attribute.identifier, type: V.self)
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
    
    public func valueAndFlags<V>(of input: Attribute<V>, options: OGValueOptions) -> (value: V, flags: OGChangedValueFlags) {
        let value = OGGraphGetInputValue(attribute, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.changed ? ._1 : []
        )
    }
    
    public func changedValue<V>(of input: Attribute<V>, options: OGValueOptions) -> (value: V, changed: Bool) {
        let value = OGGraphGetInputValue(attribute, input: input.identifier, options: options, type: V.self)
        return (
            value.value.assumingMemoryBound(to: V.self).pointee,
            value.changed
        )
    }
    
    public func update(body: () -> Void) {
        OGGraphWithUpdate(attribute, body: body)
    }
    
    public func unsafeCast<V>(to _: V.Type) -> RuleContext<V> {
        RuleContext(attribute: Attribute(identifier: attribute))
    }
}
