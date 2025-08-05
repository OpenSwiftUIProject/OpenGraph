//
//  DebugServerMessageHeader.swift
//  OpenGraphShims

@_spi(Debug)
public struct DebugServerMessageHeader {
    public let token: UInt32
    public let unknown: UInt32
    public let length: UInt32
    public let unknown2: UInt32

    public init(token: UInt32, unknown: UInt32, length: UInt32, unknown2: UInt32) {
        self.token = token
        self.unknown = unknown
        self.length = length
        self.unknown2 = unknown2
    }
}
