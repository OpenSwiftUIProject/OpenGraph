#!/bin/bash

## xcframework does not support soft link header file, so we use this script to simpfy the process.

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

AG_ROOT="$(dirname $(filepath $0))"
VERSION=${OPENGRAPH_ATTRIBUTEGRAPH_VERSION:-RELEASE_2024}

generate_swiftinterface_header() {
    local target="$1"
    local result=""
    result+="// swift-interface-format-version: 1.0\n"
    result+="// swift-compiler-version: Apple Swift version 5.7.2 (swiftlang-5.7.2.135.5 clang-1400.0.29.51)\n"
    result+="// swift-module-flags: -target $target -enable-objc-interop -enable-library-evolution -swift-version 5 -enforce-exclusivity=checked -O -module-name AttributeGraph\n"
    result+="// swift-module-flags-ignorable: -enable-bare-slash-regex"

    echo -e $result
}

generate_swiftinterface() {
  local name="$1".swiftinterface
  local target="$2"
  generate_swiftinterface_header $target > $name
  cat template.swiftinterface >> $name
}

generate_framework() {
    local framework_name=$1
    local arch_name=$2

    local path="${AG_ROOT}/${framework_name}.xcframework/${arch_name}/${framework_name}.framework"

    rm -rf ${path}/${framework_name}.tbd
    rm -rf ${path}/Headers
    rm -rf ${path}/Modules
    rm -rf ${path}/Info.plist

    cp ${AG_ROOT}/tbds/${VERSION}/${arch_name}/${framework_name}.tbd ${path}/
    cp -rf ${AG_ROOT}/Sources/Headers ${path}/
    cp -rf ${AG_ROOT}/Sources/Modules ${path}/
    cp -rf ${AG_ROOT}/Sources/Info.plist ${path}/

    cd ${path}/Modules/${framework_name}.swiftmodule
}

framework_name=AttributeGraph

generate_framework $framework_name ios-arm64-x86_64-simulator
generate_swiftinterface x86_64-apple-ios-simulator x86_64-apple-ios11.0-simulator
generate_swiftinterface arm64-apple-ios-simulator arm64-apple-ios11.0-simulator
rm template.swiftinterface

generate_framework $framework_name ios-arm64-arm64e
generate_swiftinterface arm64-apple-ios arm64e-apple-ios11.0 
generate_swiftinterface arm64e-apple-ios arm64e-apple-ios11.0 
rm template.swiftinterface

generate_framework $framework_name macos-arm64e-arm64-x86_64
generate_swiftinterface x86_64-apple-macos x86_64-apple-macos12.0
generate_swiftinterface arm64-apple-macos arm64-apple-macos12.0
generate_swiftinterface arm64e-apple-macos arm64e-apple-macos12.0
rm template.swiftinterface