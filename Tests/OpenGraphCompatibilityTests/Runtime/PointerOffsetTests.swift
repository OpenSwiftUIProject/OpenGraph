//
//  PointerOffsetTests.swift
//
//
//  Created by Kyle on 2024/2/19.
//

import Testing

struct PointerOffsetTests {
    struct PlainStruct {
        var a = 4
        var b = 5
    }
    
    class PlainClass {
        var a = 3
        var b = PlainStruct()
    }
    
    @Test
    func basic() {
        #expect(PointerOffset<PlainStruct, Int>(byteOffset: 8).byteOffset == 8)
        #expect(PointerOffset<PlainStruct, PlainStruct>().byteOffset == 0)
        let invalidPointer = PointerOffset<PlainStruct, Int>.invalidScenePointer()
        #expect(invalidPointer == UnsafeMutablePointer(bitPattern: MemoryLayout<PlainStruct>.stride))
    }
    
    @Test
    func addLogic() {
        let offset1 = PointerOffset<PlainClass, PlainStruct>(byteOffset: 8)
        let offset2 = PointerOffset<PlainStruct, Int>(byteOffset: 8)
        let result = offset1 + offset2
        #expect(result.byteOffset == 16)
    }
    
    @Test(.disabled("TODO: Add appropriate PointerOffset.of and PointerOffset.offset test case"))
    func ofAndOffset() {
        let pc = PlainClass()
        let b = PointerOffset<PlainClass, PlainStruct>.of(&pc.b)
        let c = PointerOffset<PlainStruct, Int>.of(&pc.b.b)
        let d: PointerOffset<PlainClass, Int> = b + c
        #expect(d.byteOffset == 16)
        _ = PointerOffset<PlainClass, Int>.offset { _ in
            .init(byteOffset: 0)
        }
    }
}
