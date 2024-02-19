//
//  PointerOffset.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/19.
//  Lastest Version: iOS 15.5
//  Status: WIP

@frozen
public struct PointerOffset<Base, Member> {
    public var byteOffset: Int
    
    public init(byteOffset: Int) {
        self.byteOffset = byteOffset
    }
}

extension PointerOffset {
    public static func + <A>(_ lhs: PointerOffset<Base, A>, _ rhs: PointerOffset<A, Member>) -> PointerOffset {
        PointerOffset(byteOffset: lhs.byteOffset + rhs.byteOffset)
    }
}

extension PointerOffset {
    public static func invalidScenePointer() -> UnsafeMutablePointer<Base> {
        UnsafeMutablePointer(bitPattern: MemoryLayout<Base>.stride)!
    }
    
    public static func of(_ member: inout Member) -> PointerOffset {
        withUnsafePointer(to: member) { memberPointer in
            let offset = UnsafeRawPointer(memberPointer) - UnsafeRawPointer(invalidScenePointer())
            return PointerOffset(byteOffset: offset)
        }
    }
    
    public static func offset(_ body: (inout Base) -> PointerOffset) -> PointerOffset {
        guard MemoryLayout<Member>.size != 0 else {
            return PointerOffset(byteOffset: 0)
        }
        return body(&invalidScenePointer().pointee)
    }
}

extension PointerOffset where Base == Member {
    public init() { byteOffset = 0 }
}
