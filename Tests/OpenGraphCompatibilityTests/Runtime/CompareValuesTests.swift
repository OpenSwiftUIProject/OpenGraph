//
//  CompareValuesTests.swift
//
//
//  Created by Kyle on 2023/12/20.
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "OGCompareValues is not implemented"))
struct CompareValuesTests {
    @Test
    func intCompare() throws {
        #expect(compareValues(1, 1) == true)
        #expect(compareValues(1, 2) == false)
    }

    @Test
    func enumCompare() throws {
        enum A { case a, b }
        #expect(compareValues(A.a, A.a) == true)
        #expect(compareValues(A.a, A.b) == false)

        enum B { case a, b, c }
        let b = B.b
        withUnsafePointer(to: b) { p in
            p.withMemoryRebound(to: A.self, capacity: MemoryLayout<A>.size) { pointer in
                #expect(compareValues(pointer.pointee, A.b) == true)
            }
        }
        withUnsafePointer(to: b) { p in
            p.withMemoryRebound(to: A.self, capacity: MemoryLayout<A>.size) { pointer in
                #expect(compareValues(pointer.pointee, A.a) == false)
            }
        }
    }

    @Test
    func testStructCompare() throws {
        struct A1 {
            var a: Int
            var b: Bool
        }
        struct A2 {
            var a: Int
            var b: Bool
        }
        let a = A1(a: 1, b: true)
        let b = A1(a: 1, b: true)
        let c = A1(a: 1, b: false)
        #expect(compareValues(b, a) == true)
        #expect(compareValues(c, a) == false)
        let d = A2(a: 1, b: true)
        withUnsafePointer(to: d) { p in
            p.withMemoryRebound(to: A1.self, capacity: MemoryLayout<A1>.size) { pointer in
                #expect(compareValues(pointer.pointee, a) == true)
            }
        }
        withUnsafePointer(to: d) { p in
            p.withMemoryRebound(to: A1.self, capacity: MemoryLayout<A1>.size) { pointer in
                #expect(compareValues(pointer.pointee, c) == false)
            }
        }
    }
}
