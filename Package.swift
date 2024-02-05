// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import Foundation
import PackageDescription

// https://github.com/llvm/llvm-project/issues/48757
let clangEnumFixSetting = CSetting.unsafeFlags(["-Wno-elaborated-enum-base"], .when(platforms: [.linux]))

let openGraphShimsTarget = Target.target(
    name: "OpenGraphShims"
)

let openGraphTestTarget = Target.testTarget(
    name: "OpenGraphTests",
    dependencies: [
        "OpenGraph",
    ]
)
let openGraphCompatibilityTestTarget = Target.testTarget(
    name: "OpenGraphCompatibilityTests",
    exclude: ["README.md"]
)

let swiftBinPath = Context.environment["_"] ?? ""
let swiftBinURL = URL(fileURLWithPath: swiftBinPath)
let SDKPath = swiftBinURL.deletingLastPathComponent().deletingLastPathComponent().path
let includePath = SDKPath.appending("/lib/swift_static")

let package = Package(
    name: "OpenGraph",
    platforms: [
        .iOS(.v13),
        .macOS(.v10_15),
        .macCatalyst(.v13),
        .tvOS(.v13),
        .watchOS(.v6),
        .visionOS(.v1),
    ],
    products: [
        .library(name: "OpenGraphShims", targets: ["OpenGraphShims"]),
        .library(name: "OpenGraph", targets: ["OpenGraph"]),
    ],
    targets: [
        // FIXME: Merge into one target
        // OpenGraph is a C++ & Swift mix target.
        // The SwiftPM support for such usage is still in progress.
        .target(
            name: "_OpenGraph",
            cSettings: [
                clangEnumFixSetting,
                .unsafeFlags(["-I", includePath]),
                .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1"),
            ],
            cxxSettings: [
                .unsafeFlags(["-I", "/home/kyle/.swiftbox/toolchain/swift-5.9.2/usr/lib/swift_static"]),
                .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1"),
            ]
        ),
        .target(
            name: "OpenGraph",
            dependencies: ["_OpenGraph"],
            cSettings: [clangEnumFixSetting]
        ),
        openGraphShimsTarget,
        openGraphTestTarget,
        openGraphCompatibilityTestTarget,
    ],
    cxxLanguageStandard: .cxx14
)

func envEnable(_ key: String, default defaultValue: Bool = false) -> Bool {
    guard let value = Context.environment[key] else {
        return defaultValue
    }
    if value == "1" {
        return true
    } else if value == "0" {
        return false
    } else {
        return defaultValue
    }
}

#if os(macOS)
// FIXME: Enable it by default will cause non-iOS/macOS Apple OS build fail currently.
// Add the corresponding tbd file and framework to fix it.
let attributeGraphCondition = envEnable("OPENGRAPH_ATTRIBUTEGRAPH", default: true)
#else
let attributeGraphCondition = envEnable("OPENGRAPH_ATTRIBUTEGRAPH")
#endif
if attributeGraphCondition {
    let attributeGraphProduct = Product.library(name: "AttributeGraph", targets: ["AttributeGraph"])
    let attributeGraphTarget = Target.binaryTarget(name: "AttributeGraph", path: "AG/AttributeGraph.xcframework")
    package.products.append(attributeGraphProduct)
    package.targets.append(attributeGraphTarget)
    
    var swiftSettings: [SwiftSetting] = (openGraphShimsTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_ATTRIBUTEGRAPH"))
    openGraphShimsTarget.swiftSettings = swiftSettings
    openGraphShimsTarget.dependencies.append("AttributeGraph")
} else {
    openGraphShimsTarget.dependencies.append("OpenGraph")
}

let compatibilityTestCondition = envEnable("OPENGRAPH_COMPATIBILITY_TEST")
if compatibilityTestCondition && attributeGraphCondition {
    openGraphCompatibilityTestTarget.dependencies.append("AttributeGraph")
    var swiftSettings: [SwiftSetting] = (openGraphCompatibilityTestTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_COMPATIBILITY_TEST"))
    openGraphCompatibilityTestTarget.swiftSettings = swiftSettings
} else {
    openGraphCompatibilityTestTarget.dependencies.append("OpenGraph")
}

// Remove this when swift-testing is 1.0.0
let swiftTestingCondition = envEnable("OPENGRAPH_SWIFT_TESTING")
if swiftTestingCondition {
    package.dependencies.append(
        .package(url: "https://github.com/apple/swift-testing", from: "0.2.0")
    )
    openGraphTestTarget.dependencies.append(
        .product(name: "Testing", package: "swift-testing")
    )
    var swiftSettings: [SwiftSetting] = (openGraphTestTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_SWIFT_TESTING"))
    openGraphTestTarget.swiftSettings = swiftSettings
}
