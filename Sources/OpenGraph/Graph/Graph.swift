//
//  Graph.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: WIP

public import OpenGraphCxx

extension Graph {
    public static func typeIndex(
        ctx: GraphContext,
        body: _AttributeBody.Type,
        valueType: Metadata,
        flags: _AttributeType.Flags,
        update: AttributeUpdateBlock
    ) -> Int {
        // TODO: __AGGraphInternAttributeType
        0
    }
}

@_silgen_name("OGGraphSetInvalidationCallback")
private func OGGraphSetInvalidationCallback(
    graph: Graph,
    _ callback: @escaping (AnyAttribute) -> Void
)

@_silgen_name("OGGraphSetUpdateCallback")
private func OGGraphSetUpdateCallback(
    graph: Graph,
    _ callback: @escaping () -> Void
)

extension Graph {
    public static func withoutUpdate<V>(_ body: () -> V) -> V {
        let update = clearUpdate()
        defer { setUpdate(update) }
        return body()
    }

    public func withoutSubgraphInvalidation<V>(_ body: () -> V) -> V {
        preconditionFailure("TODO")
    }

    public func withDeadline<V>(
        _: UInt64,
        _: () -> V
    ) -> V {
        preconditionFailure("TODO")
    }

    public func onInvalidation(_ callback: @escaping (AnyAttribute) -> Void) {
        OGGraphSetInvalidationCallback(graph: self, callback)
    }

    public func onUpdate(_ callback: @escaping () -> Void) {
        OGGraphSetUpdateCallback(graph: self, callback)
    }

    public func withMainThreadHandler(_: (() -> Void) -> Void, do: () -> Void) {
        // TODO: OGGraphWithMainThreadHandler
        preconditionFailure("TODO")
    }
}

extension Graph {
    public static func startProfiling() {
        __OGGraphStartProfiling(nil)
    }

    public static func stopProfiling() {
        __OGGraphStopProfiling(nil)
    }

    public static func resetProfile() {
        __OGGraphResetProfile(nil)
    }
}

extension Graph {
    @_transparent
    @inline(__always)
    public var mainUpdates: Int { numericCast(counter(for: .mainThreadUpdates)) }
}

extension Graph {
    // NOTE: Currently Swift does not support generic computed variable
    @_silgen_name("OGGraphGetOutputValue")
    @inline(__always)
    @inlinable
    public static func outputValue<Value>() -> UnsafePointer<Value>?

    @_silgen_name("OGGraphSetOutputValue")
    @inline(__always)
    @inlinable
    public static func setOutputValue<Value>(_ value: UnsafePointer<Value>)
}

extension Graph {
    @_transparent
    public static func anyInputsChanged(excluding excludedInputs: [AnyAttribute]) -> Bool {
        return __OGGraphAnyInputsChanged(excludedInputs, excludedInputs.count)
    }
}

#if canImport(Darwin)
import Foundation
#endif

extension Graph {
    public func archiveJSON(name: String?) {
        #if canImport(Darwin)
        let options: NSDictionary = [
            DescriptionOption.format: "graph/dict",
            DescriptionOption.includeValues: true,
        ]
        guard let description = Graph.description(self, options: options) as? [String: Any] else {
            return
        }
        var name = name ?? "graph"
        name.append(".ag-json")
        let path = (NSTemporaryDirectory() as NSString).appendingPathComponent(name)
        guard let data = try? JSONSerialization.data(withJSONObject: description, options: []) else {
            return
        }
        let url = URL(fileURLWithPath: path)
        do {
            try data.write(to: url, options: [])
            print("Wrote graph data to \"\(path)\".")
        } catch {
        }
        #endif
    }
}
