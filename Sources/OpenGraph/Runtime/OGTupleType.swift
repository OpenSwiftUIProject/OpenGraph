//
//  OGTupleType.swift
//
//
//

public import OpenGraph_SPI

@_silgen_name("OGTupleElementType")
@inline(__always)
private func OGTupleElementType(_ tupleType: OGTupleType, index: Int) -> Metadata

// TODO
extension OGTupleType {
    public init(_ type: [Any.Type]) {
        fatalError("TODO")
    }
    
    public init(_ type: Any.Type) {
        self.init(rawValue: unsafeBitCast(type, to: UnsafePointer<OGSwiftMetadata>.self))
    }
    
    public var type: Any.Type {
        unsafeBitCast(rawValue, to: Any.Type.self)
    }
    
    public var isEmpty: Bool {
        count == 0
    }
    
    public var indices: Range<Int> {
        0 ..< count
    }
    
    public func type(at index: Int) -> Any.Type {
        OGTupleElementType(self, index: index).type
    }
}
