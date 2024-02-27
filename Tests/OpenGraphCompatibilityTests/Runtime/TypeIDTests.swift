//
//  TypeIDTests.swift
//
//
//

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "OGTypeID is not implemented"))
struct TypeIDTests {
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
    
    @Test
    func description() {
        #expect(OGTypeID(T1.self).description == "TypeIDTests.T1")
        #expect(OGTypeID(T2.self).description == "TypeIDTests.T2")
        #expect(OGTypeID(T3.self).description == "TypeIDTests.T3")
    }
    
    @Test
    func forEachField() throws {
        for options in [OGTypeApplyOptions._1] {
            let result = OGTypeID(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 24 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == true)
        }
        for options in [OGTypeApplyOptions._2, ._4, []] {
            let result = OGTypeID(T1.self).forEachField(options: options) { name, offset, type in
                if offset == 16 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 24 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == false)
        }
        for options in [OGTypeApplyOptions._2, []] {
            let result = OGTypeID(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    #expect(type is Int.Type)
                    return true
                } else if offset == 8 {
                    #expect(type is Double.Type)
                    return true
                } else {
                    return false
                }
            }
            #expect(result == true)
        }
        for options in [OGTypeApplyOptions._1, ._4] {
            let result = OGTypeID(T2.self).forEachField(options: options) { name, offset, type in
                if offset == 0 {
                    #expect(type is Int.Type)
                    #expect(String(cString: name) == "a")
                    return true
                } else if offset == 8 {
                    #expect(type is Double.Type)
                    #expect(String(cString: name) == "b")
                    return true
                } else {
                    return false
                }
            }
            #expect(result == false)
        }
        for options in [OGTypeApplyOptions._1, ._2, ._4, []] {
            let result = OGTypeID(T3.self).forEachField(options: options) { _, _, _ in
                true
            }
            #expect(result == false)
        }
    }
}
