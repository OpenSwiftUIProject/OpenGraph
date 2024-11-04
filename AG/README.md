## AttributeGraph

### update.sh

After making change to Sources, run `update.sh` to update the xcframework.

### tbd

#### Version OS_RELEASE 2021

- iOS's tbd is from https://github.com/xybp888/iOS-SDKs/blob/master/iPhoneOS15.5.sdk/System/Library/PrivateFrameworks/AttributeGraph.framework/AttributeGraph.tbd
    - Or if you have an iOS 15.5 device, you can make it by `tbd -p --ignore-weak-def-syms -r -v4 "~/Library/Developer/Xcode/iOS DeviceSupport/iPhone16,1 17.2.1 (21C66)/Symbols/System/Library/PrivateFrameworks/AttributeGraph.framework" -o ./`
- iOS Simulator's tbd is build by `tbd -p --ignore-weak-def-syms -r -v4 "/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS 15.5.simruntime/Contents/Resources/RuntimeRoot/System/Library/PrivateFrameworks/AttributeGraph.framework" -o ./`
- macOS's tbd is from macOS 12.3 SDK(bundled with Xcode 13.4.1)

#### Version OS_RELEASE 2024

- iOS's tbd is from
    - `https://github.com/xybp888/iOS-SDKs/blob/master/iPhoneOS18.0.sdk/System/Library/PrivateFrameworks/AttributeGraph.framework/AttributeGraph.tbd` 
- iOS Simulator: 
    - `/Library/Developer/CoreSimulator/Volumes/iOS_22A3351/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS 18.0.simruntime/Contents/Resources/RuntimeRoot/System/Library/PrivateFrameworks/AttributeGraph.framework`
    - `xcrun tapi stubify ./AttributeGraph.framework`

- macOS's tbd is from macOS 15.0 SDK (bundled with Xcode 16.0)
    - `/Applications/Xcode-16.0.0.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX-15.0.sdk/System/Library/PrivateFrameworks/AttributeGraph.framework`
    - `xcrun tapi stubify ./AttributeGraph.framework`

