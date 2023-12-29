// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import Foundation
import PackageDescription

let isXcodeEnv = ProcessInfo.processInfo.environment["__CFBundleIdentifier"] == "com.apple.dt.Xcode"
// Xcode use clang as linker which supports "-iframework" while SwiftPM use swiftc as linker which supports "-Fsystem"
let systemFrameworkSearchFlag = isXcodeEnv ? "-iframework" : "-Fsystem"

// https://github.com/llvm/llvm-project/issues/48757
let clangEnumFixSetting = CSetting.unsafeFlags(["-Wno-elaborated-enum-base"], .when(platforms: [.linux]))

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
        .library(name: "OpenGraph", targets: ["OpenGraph"]),
    ],
    dependencies: [
        .package(url: "https://github.com/OpenSwiftUIProject/OpenFoundation", from: "0.0.1"),
    ],
    targets: [
        // FIXME: Merge into one target
        // OpenGraph is a C++ & Swift mix target.
        // The SwiftPM support for such usage is still in progress.
        .target(
            name: "_OpenGraph",
            dependencies: [.product(name: "OpenFoundation", package: "OpenFoundation")],
            cSettings: [clangEnumFixSetting]
        ),
        .target(
            name: "OpenGraph",
            dependencies: ["_OpenGraph"],
            cSettings: [clangEnumFixSetting]
        ),
        openGraphTestTarget,
        openGraphCompatibilityTestTarget,
    ]
)

func envEnable(_ key: String, default defaultValue: Bool = false) -> Bool {
    guard let value = ProcessInfo.processInfo.environment[key] else {
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

#if canImport(Darwin)
let attributeGraphProduct = Product.library(name: "AttributeGraph", targets: ["AttributeGraph"])
let attributeGraphTarget = Target.binaryTarget(name: "AttributeGraph", path: "AG/AttributeGraph.xcframework")
package.products.append(attributeGraphProduct)
package.targets.append(attributeGraphTarget)
#endif

let compatibilityTestCondition = envEnable("OPENGRAPH_COMPATIBILITY_TEST", default: true)
if compatibilityTestCondition {
    openGraphCompatibilityTestTarget.dependencies.append("AttributeGraph")
    var swiftSettings: [SwiftSetting] = (openGraphCompatibilityTestTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_COMPATIBILITY_TEST"))
    openGraphCompatibilityTestTarget.swiftSettings = swiftSettings

    var linkerSettings = openGraphCompatibilityTestTarget.linkerSettings ?? []
    linkerSettings.append(.unsafeFlags([systemFrameworkSearchFlag, "/System/Library/PrivateFrameworks/"], .when(platforms: [.macOS])))
    linkerSettings.append(.linkedFramework("AttributeGraph", .when(platforms: [.macOS])))
    openGraphCompatibilityTestTarget.linkerSettings = linkerSettings
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
