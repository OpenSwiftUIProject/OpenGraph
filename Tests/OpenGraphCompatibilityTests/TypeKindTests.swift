//
//  TypeKindTests.swift
//
//
//  Created by Kyle on 2024/1/8.
//

import XCTest

private protocol P {}

final class TypeKindTests: XCTestCase {
    class T1 {}
    struct T2 {}
    enum T3 {}
    
    override func setUp() async throws {
        #if !OPENGRAPH_COMPATIBILITY_TEST
        throw XCTSkip("OGTypeID.kind is not implemented")
        #endif
    }
    
    func testKind() throws {
        XCTAssertEqual(OGTypeID(T1.self).kind, .class)
        XCTAssertEqual(OGTypeID(T2.self).kind, .struct)
        XCTAssertEqual(OGTypeID(T3.self).kind, .enum)
        
        XCTAssertEqual(OGTypeID(Void?.self).kind, .optional)
        XCTAssertEqual(OGTypeID(Int?.self).kind, .optional)
        XCTAssertEqual(OGTypeID(T1?.self).kind, .optional)
        
        XCTAssertEqual(OGTypeID(Void.self).kind, .tuple)
        XCTAssertEqual(OGTypeID((Int, Double).self).kind, .tuple)
        XCTAssertEqual(OGTypeID((T1, T2, T3).self).kind, .tuple)
        
        XCTAssertEqual(OGTypeID((() -> Void).self).kind, .function)
        XCTAssertEqual(OGTypeID(P.self).kind, .existential)
        XCTAssertEqual(OGTypeID((any P).self).kind, .existential)
        
        XCTAssertEqual(OGTypeID(P.Protocol.self).kind, .metatype)
        XCTAssertEqual(OGTypeID(type(of: Int.self)).kind, .metatype)
    }
}
