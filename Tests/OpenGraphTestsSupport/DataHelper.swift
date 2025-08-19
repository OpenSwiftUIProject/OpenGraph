//
//  DataHelper.swift
//  OpenGraphTestsSupport

public struct Tuple<A, B> {
    public var first: A
    public var second: B

    public init(first: A, second: B) {
        self.first = first
        self.second = second
    }
}

public struct Triple<A, B, C> {
    public var first: A
    public var second: B
    public var third: C

    public init(first: A, second: B, third: C) {
        self.first = first
        self.second = second
        self.third = third
    }
}
