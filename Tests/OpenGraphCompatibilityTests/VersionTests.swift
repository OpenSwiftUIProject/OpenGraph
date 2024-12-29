//
//  VersionTests.swift
//  OpenGraphCompatibilityTests

import Testing
import Numerics

struct VersionTests {
    @Test
    func versionNumber() async {
        await confirmation { confirm in
            #if OPENGRAPH_COMPATIBILITY_TEST
            switch Int32(ATTRIBUTEGRAPH_RELEASE) {
                case ATTRIBUTEGRAPH_RELEASE_2021:
                    #expect(AGVersion == 0x20014)
                    confirm()
                case ATTRIBUTEGRAPH_RELEASE_2024:
                    #expect(AGVersion == 0x2001e)
                    confirm()
                default:
                    break
            }
            #else
            switch Int32(OPENGRAPH_RELEASE) {
                case OPENGRAPH_RELEASE_2021:
                    #expect(OpenGraphVersionNumber.isApproximatelyEqual(to: 3.2))
                    #expect(OGVersion == 0x20014)
                    confirm()
                case OPENGRAPH_RELEASE_2024:
                    #expect(OpenGraphVersionNumber.isApproximatelyEqual(to: 6.0))
                    #expect(OGVersion == 0x2001e)
                    confirm()
                default:
                    break
            }
            #endif
        }
    }
}
