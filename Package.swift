// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import Foundation
import PackageDescription

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

let isXcodeEnv = Context.environment["__CFBundleIdentifier"] == "com.apple.dt.Xcode"

var sharedSwiftSettings: [SwiftSetting] = []

let warningsAsErrorsCondition = envEnable("OPENGRAPH_WERROR", default: isXcodeEnv)
if warningsAsErrorsCondition {
    sharedSwiftSettings.append(.unsafeFlags(["-warnings-as-errors"]))
}

let openGraphShimsTarget = Target.target(
    name: "OpenGraphShims",
    swiftSettings: sharedSwiftSettings
)

let openGraphTestTarget = Target.testTarget(
    name: "OpenGraphTests",
    dependencies: [
        "OpenGraph",
    ],
    exclude: ["README.md"],
    swiftSettings: sharedSwiftSettings
)
let openGraphCompatibilityTestTarget = Target.testTarget(
    name: "OpenGraphCompatibilityTests",
    exclude: ["README.md"],
    swiftSettings: sharedSwiftSettings
)
let openGraphTempTestTarget = Target.testTarget(
    name: "OpenGraphTempTests",
    exclude: ["README.md"]
)

let swiftBinPath = Context.environment["_"] ?? ""
let swiftBinURL = URL(fileURLWithPath: swiftBinPath)
let SDKPath = swiftBinURL.deletingLastPathComponent().deletingLastPathComponent().deletingLastPathComponent().path
let includePath = SDKPath.appending("/usr/lib/swift_static")

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
                .unsafeFlags(["-I", includePath], .when(platforms: .nonDarwinPlatforms)),
                .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1", .when(platforms: .nonDarwinPlatforms)),
            ],
            cxxSettings: [
                .unsafeFlags(["-I", includePath], .when(platforms: .nonDarwinPlatforms)),
                .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1", .when(platforms: .nonDarwinPlatforms)),
            ]
        ),
        .target(
            name: "OpenGraph",
            dependencies: ["_OpenGraph"],
            swiftSettings: sharedSwiftSettings
        ),
        .plugin(
            name: "UpdateModule",
            capability: .command(
                intent: .custom(verb: "update-module", description: "Update AG xcframework"),
                permissions: [.writeToPackageDirectory(reason: "Update AG xcframework")]
            )
        ),
        openGraphShimsTarget,
    ],
    cxxLanguageStandard: .cxx17
)

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

// Remove this when swift-testing is 1.0.0
let swiftTestingCondition = envEnable("OPENGRAPH_SWIFT_TESTING", default: true)
if swiftTestingCondition {
    package.dependencies.append(
        // Fix it to be 0.3.0 before we bump to Swift 5.10
        .package(url: "https://github.com/apple/swift-testing", exact: "0.3.0")
    )
    openGraphTestTarget.dependencies.append(
        .product(name: "Testing", package: "swift-testing")
    )
    package.targets.append(openGraphTestTarget)
    openGraphCompatibilityTestTarget.dependencies.append(
        .product(name: "Testing", package: "swift-testing")
    )
    package.targets.append(openGraphCompatibilityTestTarget)
    openGraphTempTestTarget.dependencies.append(
        .product(name: "Testing", package: "swift-testing")
    )
    package.targets.append(openGraphTempTestTarget)
}

let compatibilityTestCondition = envEnable("OPENGRAPH_COMPATIBILITY_TEST", default: true)
if compatibilityTestCondition && attributeGraphCondition {
    openGraphCompatibilityTestTarget.dependencies.append("AttributeGraph")
    openGraphTempTestTarget.dependencies.append("AttributeGraph")
    var swiftSettings: [SwiftSetting] = (openGraphCompatibilityTestTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_COMPATIBILITY_TEST"))
    openGraphCompatibilityTestTarget.swiftSettings = swiftSettings
    openGraphTempTestTarget.swiftSettings = swiftSettings
} else {
    openGraphCompatibilityTestTarget.dependencies.append("OpenGraph")
    openGraphTempTestTarget.dependencies.append("OpenGraph")
}

extension [Platform] {
    static var nonDarwinPlatforms: [Platform] {
        [.linux, .android, .wasi, .openbsd, .windows]
    }
}
