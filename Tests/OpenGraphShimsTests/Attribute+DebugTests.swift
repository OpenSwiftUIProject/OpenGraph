//
//  Attribute+DebugTests.swift
//  OpenGraphShimsTests

import Testing
import OpenGraphShims

@MainActor
@Suite(.disabled(if: !attributeGraphEnabled, "Subgraph is not implemented on OG"), .graphScope)
struct Attribute_DebugTests {
    @Test
    func directAttribute() {
        let attribute = Attribute(value: 3)

        #expect(attribute.debugDescription == #"""
        Attribute<Int> {
            rawValue: \#(attribute.identifier.rawValue)
            graph: \#(attribute.graph)
            (direct attribute)
            valueType: Int
            value: 3
            bodyType: External<Int>
            bodyValue:
                Int
        }
        """#)
    }

    @Test
    func indirectAttribute() {
        let tuple = Attribute(value: Tuple(first: 1, second: "2"))
        let second = tuple[keyPath: \.second]
        #expect(second.debugDescription == #"""
        Attribute<String> {
            rawValue: \#(second.identifier.rawValue)
            graph: \#(second.graph)
            (indirect attribute)
            source attribute:
                rawValue: \#(tuple.identifier.rawValue)
                graph: \#(tuple.graph)
                (direct attribute)
                valueType: Tuple<Int, String>
                value: Tuple<Int, String>(first: 1, second: "2")
                bodyType: External<Tuple<Int, String>>
                bodyValue:
                    Tuple<Int, String>
        }
        """#)
    }
}
