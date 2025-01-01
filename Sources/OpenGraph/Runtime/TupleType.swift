//
//  TupleType.swift
//  OpenGraph
//
//  Audited for iOS 18.0
//  Status: WIP

public import OpenGraph_SPI

extension TupleType {
    public init(_ types: [Any.Type]) {
        self.init(count: types.count, elements: types.map(Metadata.init))
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
        elementType(at: index).type
    }
    
    public func offset<T>(at index: Int, as type: T.Type) -> Int {
        elementOffset(at: index, type: Metadata(type))
    }
    
    public func setElement<T>(in tupleValue: UnsafeMutableRawPointer, at index: Int, from srcValue: UnsafePointer<T>, options: CopyOptions) {
        __OGTupleSetElement(self, tupleValue, index, srcValue, Metadata(T.self), options)
    }
    
    public func getElement<T>(in tupleValue: UnsafeMutableRawPointer, at index: Int, to dstValue: UnsafeMutablePointer<T>, options: CopyOptions) {
        __OGTupleGetElement(self, tupleValue, index, dstValue, Metadata(T.self), options)
    }
}
