//
//  OGTypeIDTests.swift
//  OpenGraphCompatibilityTests

import Testing

@Suite(.disabled(if: !compatibilityTestEnabled, "OGTypeID is not implemented"))
struct OGTypeIDTests {

    @Test
    func descriptor() throws {
        let n1 = try #require(OGTypeID(Int.self).nominalDescriptor)
        let n2 = try #require(OGTypeID(String.self).nominalDescriptor)
        let n3 = try #require(OGTypeID(Int.self).nominalDescriptor)
        
        #expect(n1 != n2)
        #expect(n1 == n3)
    }
}
