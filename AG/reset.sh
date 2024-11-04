#!/bin/bash

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

AG_ROOT="$(dirname $(filepath $0))"

reset_framework() {
    local framework_name=$1
    local arch_name=$2

    local path="${AG_ROOT}/${framework_name}.xcframework/${arch_name}/${framework_name}.framework"

    echo $path
    
    rm -rf ${path}/${framework_name}.tbd
    rm -rf ${path}/Headers
    rm -rf ${path}/Modules
    rm -rf ${path}/Info.plist
}

framework_name=AttributeGraph

reset_framework $framework_name ios-arm64-x86_64-simulator
reset_framework $framework_name ios-arm64-arm64e
reset_framework $framework_name macos-arm64e-arm64-x86_64
