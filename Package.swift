// swift-tools-version: 6.0
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

// MARK: - Env and Config

let isXcodeEnv = Context.environment["__CFBundleIdentifier"] == "com.apple.dt.Xcode"
let development = envEnable("OPENGRAPH_DEVELOPMENT", default: false)

let releaseVersion = Context.environment["OPENGRAPH_TARGET_RELEASE"].flatMap { Int($0) } ?? 2024

let swiftBinPath = Context.environment["_"] ?? "/usr/bin/swift"
let swiftBinURL = URL(fileURLWithPath: swiftBinPath)
let SDKPath = swiftBinURL.deletingLastPathComponent().deletingLastPathComponent().deletingLastPathComponent().path
let includePath = SDKPath.appending("/usr/lib/swift")

// MARK: - C/CXX Settings

// Source: https://github.com/swiftlang/swift/blob/main/SwiftCompilerSources/Package.swift
// To successfully build, you'll need to create a couple of symlinks to an
// existing Ninja build:
//
// cd $OPENGRAPH_SWIFT_TOOLCHAIN_PATH
// mkdir -p build/Default
// ln -s build/<Ninja-Build>/llvm-<os+arch> build/Default/llvm
// ln -s build/<Ninja-Build>/swift-<os+arch> build/Default/swift
//
// where <project-root> is the parent directory of the swift repository.
//
// FIXME: We may want to consider generating Package.swift as a part of the
// build.

let swiftToolchainVersion = Context.environment["OPENGRAPH_SWIFT_TOOLCHAIN_VERSION"] ?? ""
let swiftToolchainPath = Context.environment["OPENGRAPH_SWIFT_TOOLCHAIN_PATH"] ?? ""

var sharedCSettings: [CSetting] = [
    .unsafeFlags(["-I", includePath], .when(platforms: .nonDarwinPlatforms)),
    .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1", .when(platforms: .nonDarwinPlatforms)),
]

if !swiftToolchainPath.isEmpty {
    sharedCSettings.append(
        .unsafeFlags(
            [
                "-static",
                "-DCOMPILED_WITH_SWIFT",
                "-DPURE_BRIDGING_MODE",
                "-UIBOutlet", "-UIBAction", "-UIBInspectable",
                "-I\(swiftToolchainPath)/swift/include",
                "-I\(swiftToolchainPath)/swift/stdlib/public/SwiftShims",
                "-I\(swiftToolchainPath)/llvm-project/llvm/include",
                "-I\(swiftToolchainPath)/llvm-project/clang/include",
                "-I\(swiftToolchainPath)/build/Default/swift/include",
                "-I\(swiftToolchainPath)/build/Default/llvm/include",
                "-I\(swiftToolchainPath)/build/Default/llvm/tools/clang/include",
            ]
        )
    )
}

if !swiftToolchainVersion.isEmpty {
    sharedCSettings.append(
        .define("OPENGRAPH_SWIFT_TOOLCHAIN_VERSION", to: swiftToolchainVersion)
    )
}

// MARK: - Swift Settings

var sharedSwiftSettings: [SwiftSetting] = [
    .enableUpcomingFeature("InternalImportsByDefault"),
    .define("OPENGRAPH_RELEASE_\(releaseVersion)"),
    .swiftLanguageMode(.v5),
]

if releaseVersion >= 2021 {
    for year in 2021 ... releaseVersion {
        sharedSwiftSettings.append(.define("OPENGRAPH_SUPPORT_\(year)_API"))
    }
}

let warningsAsErrorsCondition = envEnable("OPENGRAPH_WERROR", default: isXcodeEnv && development)
if warningsAsErrorsCondition {
    sharedSwiftSettings.append(.unsafeFlags(["-warnings-as-errors"]))
}

// MARK: - Targets

let openGraphShimsTarget = Target.target(
    name: "OpenGraphShims",
    swiftSettings: sharedSwiftSettings
)

let openGraphShimsTestTarget = Target.testTarget(
    name: "OpenGraphShimsTests",
    dependencies: [
        "OpenGraphShims",
    ],
    exclude: ["README.md"],
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
    dependencies: [
        .product(name: "RealModule", package: "swift-numerics"),
    ],
    exclude: ["README.md"],
    swiftSettings: sharedSwiftSettings
)

// MARK: - Package

let package = Package(
    name: "OpenGraph",
    products: [
        .library(name: "OpenGraph_SPI", targets: ["OpenGraph_SPI"]),
        .library(name: "OpenGraph", targets: ["OpenGraph"]),
        .library(name: "OpenGraphShims", targets: ["OpenGraphShims"]),
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-numerics", from: "1.0.2"),
    ],
    targets: [
        // FIXME: Merge into one target
        // OpenGraph is a C++ & Swift mix target.
        // The SwiftPM support for such usage is still in progress.
        .target(
            name: "OpenGraph_SPI",
            cSettings: sharedCSettings
        ),
        .target(
            name: "OpenGraph",
            dependencies: ["OpenGraph_SPI"],
            swiftSettings: sharedSwiftSettings
        ),
        openGraphShimsTarget,
        
        openGraphTestTarget,
        openGraphShimsTestTarget,
        openGraphCompatibilityTestTarget,
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
let useLocalDeps = envEnable("OPENGRAPH_USE_LOCAL_DEPS")

if attributeGraphCondition {
    let privateFrameworkRepo: Package.Dependency
    if useLocalDeps {
        privateFrameworkRepo = Package.Dependency.package(path: "../DarwinPrivateFrameworks")
    } else {
        privateFrameworkRepo = Package.Dependency.package(url: "https://github.com/OpenSwiftUIProject/DarwinPrivateFrameworks.git", branch: "main")
    }
    package.dependencies.append(privateFrameworkRepo)
    var swiftSettings: [SwiftSetting] = (openGraphShimsTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_ATTRIBUTEGRAPH"))
    openGraphShimsTarget.swiftSettings = swiftSettings
    openGraphShimsTarget.dependencies.append(
        .product(name: "AttributeGraph", package: "DarwinPrivateFrameworks")
    )
    
    let agVersion = Context.environment["DARWIN_PRIVATE_FRAMEWORKS_TARGET_RELEASE"].flatMap { Int($0) } ?? 2024
    package.platforms = switch agVersion {
        case 2024: [.iOS(.v18), .macOS(.v15), .macCatalyst(.v18), .tvOS(.v18), .watchOS(.v10), .visionOS(.v2)]
        case 2021: [.iOS(.v15), .macOS(.v12), .macCatalyst(.v15), .tvOS(.v15), .watchOS(.v7)]
        default: nil
    }
} else {
    openGraphShimsTarget.dependencies.append("OpenGraph")
}

let compatibilityTestCondition = envEnable("OPENGRAPH_COMPATIBILITY_TEST")
if compatibilityTestCondition && attributeGraphCondition {
    openGraphCompatibilityTestTarget.dependencies.append(
        .product(name: "AttributeGraph", package: "DarwinPrivateFrameworks")
    )
    
    var swiftSettings: [SwiftSetting] = (openGraphCompatibilityTestTarget.swiftSettings ?? [])
    swiftSettings.append(.define("OPENGRAPH_COMPATIBILITY_TEST"))
    openGraphCompatibilityTestTarget.swiftSettings = swiftSettings
} else {
    openGraphCompatibilityTestTarget.dependencies.append("OpenGraph")
}

extension [Platform] {
    static var nonDarwinPlatforms: [Platform] {
        [.linux, .android, .wasi, .openbsd, .windows]
    }
}
