//
//  OGTypeApplyEnumData.swift
//
//
//

// public import OpenGraphCxx

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
