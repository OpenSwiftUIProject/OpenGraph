//
//  AttributeBodyVisitor.swift
//  OpenGraph
//
//  Status: WIP

public protocol AttributeBodyVisitor {
    mutating func visit<Body: _AttributeBody>(body: UnsafePointer<Body>)
}
