//
//  PointerOffsetTests.swift
//  OpenGraphCompatibilityTests

import RealModule
import Testing

struct PointerOffsetTests {
    @Test
    func plainInitAndProperty() {
        typealias Base = Tuple<Int, Int>
        var offset = PointerOffset<Base, Int>(byteOffset: 8)
        #expect(offset.byteOffset == 8)
        offset.byteOffset = 0
        #expect(offset.byteOffset == 0)
    }

    @Test
    func emptyInit() {
        #expect(PointerOffset<Void, Void>().byteOffset == 0)
        #expect(PointerOffset<Int, Int>().byteOffset == 0)
        #expect(PointerOffset<Any, Any>().byteOffset == 0)
    }

    @Test
    func plusOperator() {
        typealias Base = Tuple<Int, Int>
        typealias Base2 = Tuple<Int, Base>
        let offset1 = PointerOffset<Base2, Base>(byteOffset: 8)
        let offset2 = PointerOffset<Base, Int>(byteOffset: 8)
        let result = offset1 + offset2
        #expect(result.byteOffset == 16)
        #expect(type(of: result) == PointerOffset<Base2, Int>.self)
    }

    @Test
    func invalidScenePointer() {
        typealias Base = Tuple<Int, Int>
        let invalidPointer = PointerOffset<Base, Int>.invalidScenePointer()
        let stride = MemoryLayout<Base>.stride
        #expect(stride == 16)
        #expect(invalidPointer == UnsafeMutablePointer(bitPattern: stride))
    }

    @Test(.bug("https://github.com/OpenSwiftUIProject/OpenGraph/issues", id: 70))
    func ofAndOffset() {
        struct Empty {
            var value: Void
        }

        func helper<Base, Member>(
            expectedByteOffset: Int,
            _: Base.Type,
            _: Member.Type,
            _ body: (inout Base) -> PointerOffset<Base, Member>
        ) {
            let pointerOffsetType = PointerOffset<Base, Member>.self
            let offset = pointerOffsetType.offset { invalid in
                withUnsafeMutablePointer(to: &invalid) { pointer in
                    #expect(pointer == PointerOffset<Base, Member>.invalidScenePointer())
                }
                return body(&invalid)
            }
            #expect(offset.byteOffset == expectedByteOffset)
        }

        helper(expectedByteOffset: 0, Tuple<Int, Int>.self, Void.self) { _ in fatalError("Unreachable") }
        helper(expectedByteOffset: 0, Tuple<Int, Int>.self, Empty.self) { _ in fatalError("Unreachable") }

        typealias Base = Triple<Int, Int, Empty>
        helper(expectedByteOffset: 0, Base.self, Int.self) { invalid in
            .of(&invalid.first)
        }
        helper(expectedByteOffset: 8, Base.self, Int.self) { invalid in
            .of(&invalid.second)
        }
        helper(expectedByteOffset: 0, Base.self, Empty.self) { invalid in
            .of(&invalid.third)
        }
    }

    @Test("Extension API between UnsafePointer/UnsafeMutablePointer and PointerOffset")
    func unsafePointerAndUnsafeMutablePointerExtension() {
        do {
            var tuple = Tuple(first: 1, second: 2.0)
            typealias Base = Tuple<Int, Double>
            let firstOffset = PointerOffset<Base, Int>(byteOffset: 0)
            let secondOffset = PointerOffset<Base, Double>(byteOffset: 8)
            withUnsafePointer(to: tuple) { pointer in
                #expect(pointer[offset: firstOffset] == 1)
                #expect(pointer[offset: secondOffset].isApproximatelyEqual(to: 2.0))
            }
            withUnsafeMutablePointer(to: &tuple) { pointer in
                #expect(pointer[offset: firstOffset] == 1)
                #expect(pointer[offset: secondOffset].isApproximatelyEqual(to: 2.0))

                pointer[offset: firstOffset] = 3
                pointer[offset: secondOffset] = 4.0
                
                #expect(pointer[offset: firstOffset] == 3)
                #expect(pointer[offset: secondOffset].isApproximatelyEqual(to: 4.0))
            }
            withUnsafePointer(to: &tuple) { pointer in
                #expect(pointer[offset: firstOffset] == 3)
                #expect(pointer[offset: secondOffset].isApproximatelyEqual(to: 4.0))
            }
            #if !(!canImport(Darwin) && !DEBUG)
            withUnsafePointer(to: tuple) { pointer in
                #expect(pointer[offset: firstOffset] == 3)
                #expect(pointer[offset: secondOffset].isApproximatelyEqual(to: 4.0))
            }
            #expect(tuple.first == 3)
            #expect(tuple.second.isApproximatelyEqual(to: 4.0))
            #endif
        }

        do {
            var triple = Triple(first: 0, second: 1, third: 2)
            typealias Base = Triple<Int, Int, Int>

            let firstOffset = PointerOffset<Base, Int>.offset { .of(&$0.first) }
            let secondOffset = PointerOffset<Base, Int>.offset { .of(&$0.second) }
            let thirdOffset = PointerOffset<Base, Int>.offset { .of(&$0.third) }
            
            withUnsafePointer(to: triple) { pointer in
                #expect((pointer + firstOffset).pointee == 0)
                #expect((pointer + secondOffset).pointee == 1)
                #expect((pointer + thirdOffset).pointee == 2)
            }
            withUnsafeMutablePointer(to: &triple) { pointer in
                #expect((pointer + firstOffset).pointee == 0)
                #expect((pointer + secondOffset).pointee == 1)
                #expect((pointer + thirdOffset).pointee == 2)

                (pointer + firstOffset).pointee = 3
                (pointer + secondOffset).pointee = 4
                (pointer + thirdOffset).pointee = 5
                
                 #expect((pointer + firstOffset).pointee == 3)
                 #expect((pointer + secondOffset).pointee == 4)
                 #expect((pointer + thirdOffset).pointee == 5)
            }
            withUnsafePointer(to: &triple) { pointer in
                #expect((pointer + firstOffset).pointee == 3)
                #expect((pointer + secondOffset).pointee == 4)
                #expect((pointer + thirdOffset).pointee == 5)
            }
            #if !(!canImport(Darwin) && !DEBUG)
            withUnsafePointer(to: triple) { pointer in
                #expect((pointer + firstOffset).pointee == 3)
                #expect((pointer + secondOffset).pointee == 4)
                #expect((pointer + thirdOffset).pointee == 5)
            }
            #expect(triple.first == 3)
            #expect(triple.second == 4)
            #expect(triple.third == 5)
            #endif
        }
    }
    
    #if !canImport(Darwin) && !DEBUG
    @Test("Undefined Behavior Issue for PointerOffset", .bug("#73", relationship: .uncoveredBug))
    func unsafePointerAndUnsafeMutablePointerExtensionUB() {
        var tuple = Tuple(first: 1, second: 2)
        typealias Base = Tuple<Int, Int>
        let firstOffset = PointerOffset<Base, Int>(byteOffset: 0)
        withUnsafeMutablePointer(to: &tuple) { pointer in
            #expect(pointer[offset: firstOffset] == 1)
            pointer[offset: firstOffset] = 3
        }
        let unexpectedValue = tuple.first
        // The value will be unexpected due to UB
        #expect(unexpectedValue == 1)
        // The value will be expected after and within a withKnownIssue block
        withKnownIssue {
            let expectedValue = tuple.first
            #expect(expectedValue == 3)
            Issue.record("To make withKnownIssue pass")
        }
        let expectedValue = tuple.first
        #expect(expectedValue == 3)
    }
    #endif
}
