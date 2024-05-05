//
//  PointerOffset.swift
//  OpenGraph
//
//  Audited for RELEASE_2021
//  Status: Complete

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
        withUnsafePointer(to: &member) { memberPointer in
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

extension UnsafePointer {
    public subscript<Member>(offset offset: PointerOffset<Pointee, Member>) -> Member {
        unsafeAddress {
            UnsafeRawPointer(self)
                .advanced(by: offset.byteOffset)
                .assumingMemoryBound(to: Member.self)
        }
    }
    
    public static func + <Member>(
        _ lhs: UnsafePointer,
        _ rhs: PointerOffset<Pointee, Member>
    ) -> UnsafePointer<Member> {
        UnsafeRawPointer(lhs)
            .advanced(by: rhs.byteOffset)
            .assumingMemoryBound(to: Member.self)
    }
}

extension UnsafeMutablePointer {
    public subscript<Member>(offset offset: PointerOffset<Pointee, Member>) -> Member {
        unsafeAddress {
            UnsafeRawPointer(self)
                .advanced(by: offset.byteOffset)
                .assumingMemoryBound(to: Member.self)
        }
        
        nonmutating unsafeMutableAddress {
            UnsafeMutableRawPointer(self)
                .advanced(by: offset.byteOffset)
                .assumingMemoryBound(to: Member.self)
        }
    }
    
    public static func + <Member>(
        _ lhs: UnsafeMutablePointer,
        _ rhs: PointerOffset<Pointee, Member>
    ) -> UnsafeMutablePointer<Member> {
        UnsafeMutableRawPointer(lhs)
            .advanced(by: rhs.byteOffset)
            .assumingMemoryBound(to: Member.self)
    }
}
