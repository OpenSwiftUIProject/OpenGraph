//
//  TypeIDTests.swift
//
//
//  Created by Kyle on 2024/1/24.
//

import XCTest

final class TypeIDTests: XCTestCase {
    class T1 {
        var a = 0
        var b: Double = 0
    }

    struct T2 {
        var a: Int
        var b: Double
    }

    enum T3 {
        case a, b
    }
    
    override func setUp() async throws {
        #if !OPENGRAPH_COMPATIBILITY_TEST
        throw XCTSkip("OGTypeID is not implemented")
        #endif
    }
    
    func testDescription() {
        XCTAssertEqual(OGTypeID(T1.self).description, "TypeIDTests.T1")
        XCTAssertEqual(OGTypeID(T2.self).description, "TypeIDTests.T2")
        XCTAssertEqual(OGTypeID(T3.self).description, "TypeIDTests.T3")
    }
    
    func testForEachField() throws {
        for options in [OGTypeApplyOptions._1] {
            let result = OGTypeID(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    XCTAssertTrue(type is Int.Type)
                    XCTAssertEqual(String(cString: name), "a")
                    return true
                } else if offset == 24 {
                    XCTAssertTrue(type is Double.Type)
                    XCTAssertEqual(String(cString: name), "b")
                    return true
                } else {
                    return false
                }
            }
            XCTAssertTrue(result)
        }
        for options in [OGTypeApplyOptions._2, ._4, []] {
            let result = OGTypeID(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    XCTAssertTrue(type is Int.Type)
                    XCTAssertEqual(String(cString: name), "a")
                    return true
                } else if offset == 24 {
                    XCTAssertTrue(type is Double.Type)
                    XCTAssertEqual(String(cString: name), "b")
                    return true
                } else {
                    return false
                }
            }
            XCTAssertFalse(result)
        }
        for options in [OGTypeApplyOptions._2, []] {
            let result = OGTypeID(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    XCTAssertTrue(type is Int.Type)
                    return true
                } else if offset == 8 {
                    XCTAssertTrue(type is Double.Type)
                    return true
                } else {
                    return false
                }
            }
            XCTAssertTrue(result)
        }
        for options in [OGTypeApplyOptions._1, ._4] {
            let result = OGTypeID(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    XCTAssertTrue(type is Int.Type)
                    XCTAssertEqual(String(cString: name), "a")
                    return true
                } else if offset == 8 {
                    XCTAssertTrue(type is Double.Type)
                    XCTAssertEqual(String(cString: name), "b")
                    return true
                } else {
                    return false
                }
            }
            XCTAssertFalse(result)
        }
        for options in [OGTypeApplyOptions._1, ._2, ._4, []] {
            let result = OGTypeID(T3.self).forEachField(options: options) { _, _, _ in
                true
            }
            XCTAssertFalse(result)
        }
    }
}
