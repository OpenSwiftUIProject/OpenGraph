//
//  TupleType.swift
//  OpenGraph
//
//  Audited for iOS 18.0
//  Status: WIP

public import OpenGraph_SPI

// MARK: TupleType

extension TupleType {
    public init(_ types: [Any.Type]) {
        self.init(count: types.count, elements: types.map(Metadata.init))
    }
    
    public init(_ type: Any.Type) {
        self.init(rawValue: unsafeBitCast(type, to: UnsafePointer<_Metadata>.self))
    }
    
    public var isEmpty: Bool { count == 0 }
    public var indices: Range<Int> { 0 ..< count }
    
    public var type: Any.Type {
        unsafeBitCast(rawValue, to: Any.Type.self)
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

@_silgen_name("OGTupleWithBuffer")
public func withUnsafeTuple(of type: TupleType, count: Int, _ body: (UnsafeMutableTuple) -> ())

// MARK: - UnsafeTuple

extension UnsafeTuple {
    public var count: Int { type.count }
    public var isEmpty: Bool { type.isEmpty }
    public var indices: Range<Int> { type.indices }
    
    public func address<T>(as _: T.Type = T.self) -> UnsafePointer<T> {
        guard type.type == T.self else {
            preconditionFailure()
        }
        return value.assumingMemoryBound(to: T.self)
    }
    
    public func address<T>(of index: Int, as _: T.Type = T.self) -> UnsafePointer<T> {
        value.advanced(by: type.elementOffset(at: index, type: Metadata(T.self)))
            .assumingMemoryBound(to: T.self)
    }
    
    public subscript<T>() -> T {
        unsafeAddress { address(as: T.self) }
    }
    
    public subscript<T>(_ index: Int) -> T {
        unsafeAddress { address(of: index, as: T.self) }
    }
}

// MARK: - UnsafeMutableTuple

extension UnsafeMutableTuple {
    public init(with tupleType: TupleType) {
        self.init(
            type: tupleType,
            value: UnsafeMutableRawPointer.allocate(
                byteCount: tupleType.size,
                alignment: -1
            )
        )
    }
    
    public func initialize<T>(at index: Int, to element: T) {
        withUnsafePointer(to: element) { elementPointer in
            type.setElement(in: value, at: index, from: elementPointer, options: .initCopy)
        }
    }
    
    public func deinitialize() {
        type.destroy(value)
    }
    
    public func deinitialize(at index: Int) {
        type.destroy(value, at: index)
    }

    public func deallocate(initialized: Bool) {
        if initialized {
            deinitialize()
        }
        value.deallocate()
    }
    
    public var count: Int { type.count }
    public var isEmpty: Bool { type.isEmpty }
    public var indices: Range<Int> { type.indices }
    
    public func address<T>(as _: T.Type = T.self) -> UnsafeMutablePointer<T> {
        guard type.type == T.self else {
            preconditionFailure()
        }
        return value.assumingMemoryBound(to: T.self)
    }
    
    public func address<T>(of index: Int, as _: T.Type = T.self) -> UnsafeMutablePointer<T> {
        value.advanced(by: type.elementOffset(at: index, type: Metadata(T.self)))
            .assumingMemoryBound(to: T.self)
    }
    
    public subscript<T>() -> T {
        unsafeAddress { UnsafePointer(address(as: T.self)) }
        nonmutating unsafeMutableAddress { address(as: T.self) }
    }
    
    public subscript<T>(_ index: Int) -> T {
        unsafeAddress { UnsafePointer(address(of: index, as: T.self)) }
        nonmutating unsafeMutableAddress { address(of: index, as: T.self) }
    }
}
