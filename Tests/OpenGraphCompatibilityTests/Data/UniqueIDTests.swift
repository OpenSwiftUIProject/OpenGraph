//
//  UniqueIDTests.swift
//
//
//

import Testing

struct UniqueIDTests {
    @Test
    func uniqueID() throws {
        let initialID = makeUniqueID()
        #expect(makeUniqueID() == initialID + 1)
    }
}
