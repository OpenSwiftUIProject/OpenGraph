//
//  TableTests.swift
//  OpenGraphCxxTests

#if canImport(Darwin) // table() is not implemented on Linux yet.
import OpenGraphCxx_Private.Data
import Testing

struct TableTests {
    @Test
    func table() {
        let table = OG.data.table()
        table.print()
    }
}
#endif
