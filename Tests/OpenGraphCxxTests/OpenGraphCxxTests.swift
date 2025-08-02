//
//  OpenGraphCxxTests.swift
//  OpenGraphCxxTests

import OpenGraphCxx_Private
import Testing

struct OpenGraphCxxTests {
    #if canImport(Darwin) // table() is not implemented on Linux yet.
    @Test
    func table() {
        OG.data.table.ensure_shared()
    }
    #endif
}
