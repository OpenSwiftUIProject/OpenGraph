//
//  AttributeBodyVisitor.swift
//  OpenGraph
//
//  Created by Kyle on 2024/2/16.
//  Status: WIP

public protocol AttributeBodyVisitor {
    func visit<Body: _AttributeBody>(body: UnsafePointer<Body>)
}
