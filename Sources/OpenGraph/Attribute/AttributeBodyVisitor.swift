//
//  AttributeBodyVisitor.swift
//
//
//  Created by Kyle on 2024/2/16.
//

public protocol AttributeBodyVisitor {
    func visit<Body: _AttributeBody>(body: UnsafePointer<Body>)
}
