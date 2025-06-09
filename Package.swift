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

#if os(macOS)
// NOTE: #if os(macOS) check is not accurate if we are cross compiling for Linux platform. So we add an env key to specify it.
let buildForDarwinPlatform = envEnable("OPENSWIFTUI_BUILD_FOR_DARWIN_PLATFORM", default: true)
#else
let buildForDarwinPlatform = envEnable("OPENSWIFTUI_BUILD_FOR_DARWIN_PLATFORM")
#endif


// https://github.com/SwiftPackageIndex/SwiftPackageIndex-Server/issues/3061#issuecomment-2118821061
// By-pass https://github.com/swiftlang/swift-package-manager/issues/7580
let isSPIDocGenerationBuild = envEnable("SPI_GENERATE_DOCS", default: false)

// MARK: - Env and Config

let isXcodeEnv = Context.environment["__CFBundleIdentifier"] == "com.apple.dt.Xcode"
let development = envEnable("OPENGRAPH_DEVELOPMENT", default: false)

let swiftBinPath = Context.environment["_"] ?? "/usr/bin/swift"
let swiftBinURL = URL(fileURLWithPath: swiftBinPath)
let SDKPath = swiftBinURL.deletingLastPathComponent().deletingLastPathComponent().deletingLastPathComponent().path
let includePath = SDKPath.appending("/usr/lib/swift")

var sharedCSettings: [CSetting] = [
    .unsafeFlags(["-I", includePath], .when(platforms: .nonDarwinPlatforms)),
    .define("NDEBUG", .when(configuration: .release)),
]

var sharedSwiftSettings: [SwiftSetting] = [
    .enableUpcomingFeature("InternalImportsByDefault"),
    .enableExperimentalFeature("Extern"),
    .swiftLanguageMode(.v5),
]

// MARK: [env] OPENGRAPH_SWIFT_TOOLCHAIN_PATH

// Modified from: https://github.com/swiftlang/swift/blob/main/SwiftCompilerSources/Package.swift
//
// Create a couple of symlinks to an existing Ninja build:
//
//     ```shell
//     cd $OPENGRAPH_SWIFT_TOOLCHAIN_PATH
//     mkdir -p build/Default
//     ln -s build/<Ninja-Build>/llvm-<os+arch> build/Default/llvm
//     ln -s build/<Ninja-Build>/swift-<os+arch> build/Default/swift
//     ```
//
// where <$OPENGRAPH_SWIFT_TOOLCHAIN_PATH> is the parent directory of the swift repository.

let swiftToolchainPath = Context.environment["OPENGRAPH_SWIFT_TOOLCHAIN_PATH"] ?? (development ? "/Volumes/BuildMachine/swift-project" : "")
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
                "-DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING", // Required to fix LLVM link issue
            ]
        )
    )
}

// MARK: [env] OPENGRAPH_SWIFT_TOOLCHAIN_VERSION

let swiftToolchainVersion = Context.environment["OPENGRAPH_SWIFT_TOOLCHAIN_VERSION"] ?? (development ? "6.0.2" : "")
if !swiftToolchainVersion.isEmpty {
    sharedCSettings.append(
        .define("OPENGRAPH_SWIFT_TOOLCHAIN_VERSION", to: swiftToolchainVersion)
    )
}

// MARK: - [env] OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED

let swiftToolchainSupported = envEnable("OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED", default: !swiftToolchainVersion.isEmpty)
if swiftToolchainSupported {
    sharedCSettings.append(.define("OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED"))
    sharedSwiftSettings.append(.define("OPENGRAPH_SWIFT_TOOLCHAIN_SUPPORTED"))
}

// MARK: - [env] OPENGRAPH_TARGET_RELEASE

let releaseVersion = Context.environment["OPENGRAPH_TARGET_RELEASE"].flatMap { Int($0) } ?? 2024
sharedCSettings.append(.define("OPENGRAPH_RELEASE", to: "\(releaseVersion)"))
sharedSwiftSettings.append(.define("OPENGRAPH_RELEASE_\(releaseVersion)"))
if releaseVersion >= 2021 {
    for year in 2021 ... releaseVersion {
        sharedSwiftSettings.append(.define("OPENGRAPH_SUPPORT_\(year)_API"))
    }
}

// MARK: - [env] OPENGRAPH_WERROR

let warningsAsErrorsCondition = envEnable("OPENGRAPH_WERROR", default: isXcodeEnv && development)
if warningsAsErrorsCondition {
    sharedSwiftSettings.append(.unsafeFlags(["-warnings-as-errors"]))
}

// MARK: - [env] OPENGRAPH_LIBRARY_EVOLUTION

let libraryEvolutionCondition = envEnable("OPENGRAPH_LIBRARY_EVOLUTION", default: buildForDarwinPlatform)

if libraryEvolutionCondition {
    // NOTE: -enable-library-evolution will cause module verify failure for `swift build`.
    // Either set OPENGRAPH_LIBRARY_EVOLUTION=0 or add `-Xswiftc -no-verify-emitted-module-interface` after `swift build`
    sharedSwiftSettings.append(.unsafeFlags(["-enable-library-evolution", "-no-verify-emitted-module-interface"]))
}

// MARK: - Targets

let openGraphTarget = Target.target(
    name: "OpenGraph",
    dependencies: ["OpenGraph_SPI"],
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)
// FIXME: Merge into one target
// OpenGraph is a C++ & Swift mix target.
// The SwiftPM support for such usage is still in progress.
let openGraphSPITarget = Target.target(
    name: "OpenGraph_SPI",
    cSettings: sharedCSettings + [
        .define("__COREFOUNDATION_FORSWIFTFOUNDATIONONLY__", to: "1", .when(platforms: .nonDarwinPlatforms)),
    ]
)
let openGraphShimsTarget = Target.target(
    name: "OpenGraphShims",
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)

// MARK: - Test Targets

let openGraphTestTarget = Target.testTarget(
    name: "OpenGraphTests",
    dependencies: [
        "OpenGraph",
    ],
    exclude: ["README.md"],
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)
let openGraphSPITestTarget = Target.testTarget(
    name: "OpenGraph_SPITests",
    dependencies: [
        "OpenGraph_SPI",
    ],
    exclude: ["README.md"],
    cSettings: sharedCSettings + [
        .headerSearchPath("../../Sources/OpenGraph_SPI"),
    ],
    swiftSettings: sharedSwiftSettings,
    linkerSettings: [.linkedFramework("XCTest")]
)
let openGraphShimsTestTarget = Target.testTarget(
    name: "OpenGraphShimsTests",
    dependencies: [
        "OpenGraphShims",
    ],
    exclude: ["README.md"],
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)
let openGraphCompatibilityTestTarget = Target.testTarget(
    name: "OpenGraphCompatibilityTests",
    dependencies: [
        .product(name: "Numerics", package: "swift-numerics"),
    ],
    exclude: ["README.md"],
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)
let openGraphSPICompatibilityTestTarget = Target.testTarget(
    name: "OpenGraph_SPICompatibilityTests",
    dependencies: [
        .product(name: "Numerics", package: "swift-numerics"),
    ],
    exclude: ["README.md"],
    cSettings: sharedCSettings,
    swiftSettings: sharedSwiftSettings
)

// MARK: - Package

let package = Package(
    name: "OpenGraph",
    products: [
        .library(name: "OpenGraph", type: .dynamic, targets: ["OpenGraph", "OpenGraph_SPI"]),
        .library(name: "OpenGraphShims", type: .dynamic, targets: ["OpenGraph", "OpenGraph_SPI", "OpenGraphShims"]),
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-numerics", from: "1.0.2"),
    ],
    targets: [
        openGraphTarget,
        openGraphSPITarget,
        openGraphShimsTarget,
        
        openGraphTestTarget,
        openGraphSPITestTarget,
        openGraphShimsTestTarget,
        openGraphCompatibilityTestTarget,
        openGraphSPICompatibilityTestTarget,
    ],
    cxxLanguageStandard: .cxx20
)

extension Target {
    func addAGSettings() {
        dependencies.append(
            .product(name: "AttributeGraph", package: "DarwinPrivateFrameworks")
        )
        var swiftSettings = swiftSettings ?? []
        swiftSettings.append(.define("OPENGRAPH_ATTRIBUTEGRAPH"))
        self.swiftSettings = swiftSettings
    }
    
    func addCompatibilitySettings() {
        dependencies.append(
            .product(name: "AttributeGraph", package: "DarwinPrivateFrameworks")
        )
        var swiftSettings = swiftSettings ?? []
        swiftSettings.append(.define("OPENGRAPH_COMPATIBILITY_TEST"))
        self.swiftSettings = swiftSettings
    }
}

let useLocalDeps = envEnable("OPENGRAPH_USE_LOCAL_DEPS")

let attributeGraphCondition = envEnable("OPENGRAPH_ATTRIBUTEGRAPH", default: buildForDarwinPlatform && !isSPIDocGenerationBuild)

if attributeGraphCondition {
    let privateFrameworkRepo: Package.Dependency
    if useLocalDeps {
        privateFrameworkRepo = Package.Dependency.package(path: "../DarwinPrivateFrameworks")
    } else {
        privateFrameworkRepo = Package.Dependency.package(url: "https://github.com/OpenSwiftUIProject/DarwinPrivateFrameworks.git", branch: "main")
    }
    package.dependencies.append(privateFrameworkRepo)
    openGraphShimsTarget.addAGSettings()
    
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
    openGraphCompatibilityTestTarget.addCompatibilitySettings()
    openGraphSPICompatibilityTestTarget.addCompatibilitySettings()
} else {
    openGraphCompatibilityTestTarget.dependencies.append("OpenGraph")
    openGraphSPICompatibilityTestTarget.dependencies.append("OpenGraph")
}

extension [Platform] {
    static var nonDarwinPlatforms: [Platform] {
        [.linux, .android, .wasi, .openbsd, .windows]
    }
}
