//
//  OGTypeApplyEnumData.swift
//
//
//  Created by Kyle on 2024/1/29.
//

import _OpenGraph

@discardableResult
public func withUnsafePointerToEnumCase<T>(
    of value: UnsafeMutablePointer<T>,
    do body: (Int, Any.Type, UnsafeRawPointer) -> ()
) -> Bool {
    // TODO: OGTypeApplyEnumData
    return true
}

@discardableResult
public func withUnsafeMutablePointerToEnumCase<T>(
    of value: UnsafeMutablePointer<T>,
    do body: (Int, Any.Type, UnsafeMutableRawPointer) -> ()
) -> Bool {
    // TODO: OGTypeApplyMutableEnumData
    return true
}
