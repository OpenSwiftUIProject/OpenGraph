#!/bin/zsh

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

AG_ROOT="$(dirname $(filepath $0))"
xcframework_path="${AG_ROOT}/AttributeGraph.xcframework"
framework_name=AttributeGraph.framework

reset_framework() {
    local frmework_name=$1
    rm -rf ${xcframework_path}/${frmework_name}/${framework_name}/Headers
    rm -rf ${xcframework_path}/${frmework_name}/${framework_name}/Modules
    rm -rf ${xcframework_path}/${frmework_name}/${framework_name}/Info.plist
}

reset_framework ios-arm64-x86_64-simulator
reset_framework ios-arm64-arm64e
reset_framework macos-arm64e-arm64-x86_64
