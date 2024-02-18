//
//  UniqueIDTests.swift
//
//
//  Created by Kyle on 2023/10/9.
//

import Testing

struct UniqueIDTests {
    @Test
    func uniqueID() throws {
        let initialID = makeUniqueID()
        #expect(makeUniqueID() == initialID + 1)
    }
}
