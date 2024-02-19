//
//  PointerOffsetTests.swift
//
//
//  Created by Kyle on 2024/2/19.
//

import Testing

struct PointerOffsetTests {
    struct Tuple<A, B> {
        var first: A
        var second: B
    }

    struct Triple<A, B, C> {
        var first: A
        var second: B
        var third: C
    }
    
    @Test
    func basicInit() {
        #expect(PointerOffset<Any, Any>(byteOffset: 8).byteOffset == 8)
        #expect(PointerOffset<Int, Int>().byteOffset == 0)
        let invalidPointer = PointerOffset<Tuple<Int, Int>, Int>.invalidScenePointer()
        #expect(MemoryLayout<Tuple<Int, Int>>.stride == 16)
        #expect(invalidPointer == UnsafeMutablePointer(bitPattern: MemoryLayout<Tuple<Int, Int>>.stride))
    }
    
    @Test
    func plusOperator() {
        let offset1 = PointerOffset<Tuple<Int, Tuple<Int, Int>>, Tuple<Int, Int>>(byteOffset: 8)
        let offset2 = PointerOffset<Tuple<Int, Int>, Int>(byteOffset: 8)
        let result = offset1 + offset2
        #expect(result.byteOffset == 16)
    }
    
    @Test(.disabled("TODO: Add appropriate PointerOffset.of and PointerOffset.offset test case"))
    func ofAndOffset() {
        var tuple = Tuple(first: 1, second: 2)
        _ = PointerOffset<Tuple<Int, Int>, Int>.of(&tuple.second)
    }
    
    @Test
    func unsafePointer() {
        let tuple = Tuple(first: 1, second: 2.0)
        withUnsafePointer(to: tuple) { pointer in
            let first = pointer[offset: PointerOffset<Tuple<Int, Double>, Int>(byteOffset: 0)]
            #expect(first == 1)
            let second = pointer[offset: PointerOffset<Tuple<Int, Double>, Double>(byteOffset: 8)]
            #expect(second == 2.0)
        }
        
        let triple = Triple(first: 0, second: 1, third: 2)
        withUnsafePointer(to: triple) { pointer in
            let first = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 0)
            #expect(first.pointee == 0)
            let second = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 8)
            #expect(second.pointee == 1)
            let third = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 16)
            #expect(third.pointee == 2)
        }
    }
    
    @Test
    func unsafeMutablePointer() {
        var tuple = Tuple(first: 1, second: 2.0)
        withUnsafeMutablePointer(to: &tuple) { pointer in
            let first = pointer[offset: PointerOffset<Tuple<Int, Double>, Int>(byteOffset: 0)]
            #expect(first == 1)
            let second = pointer[offset: PointerOffset<Tuple<Int, Double>, Double>(byteOffset: 8)]
            #expect(second == 2.0)
            
            pointer[offset: PointerOffset<Tuple<Int, Double>, Int>(byteOffset: 0)] = 3
            let newFirst = pointer[offset: PointerOffset<Tuple<Int, Double>, Int>(byteOffset: 0)]
            #expect(newFirst == 3)
        }
        
        var triple = Triple(first: 0, second: 1, third: 2)
        withUnsafeMutablePointer(to: &triple) { pointer in
            let first = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 0)
            #expect(first.pointee == 0)
            let second = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 8)
            #expect(second.pointee == 1)
            let third = pointer + PointerOffset<Triple<Int, Int, Int>, Int>(byteOffset: 16)
            #expect(third.pointee == 2)
        }
    }
}
