//
//  OpenGraph_SPITests.swift
//  OpenGraph

import OpenGraph_SPI.Cxx
import Testing

struct OpenGraph_SPITests {
    #if canImport(Darwin) // table() is not implemented on Linux yet.
    @Test
    func table() {
        OG.data.table.ensure_shared()
    }
    #endif
}
