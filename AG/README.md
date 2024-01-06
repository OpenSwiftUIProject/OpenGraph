## AttributeGraph

### update.sh

After making change to Sources, run `update.sh` to update the xcframework.

### tbd

- iOS's tbd is from https://github.com/xybp888/iOS-SDKs/blob/master/iPhoneOS15.5.sdk/System/Library/PrivateFrameworks/AttributeGraph.framework/AttributeGraph.tbd
    - Or if you have an iOS 15.5 device, you can make it by `tbd -p --ignore-weak-def-syms -r -v4 "~/Library/Developer/Xcode/iOS DeviceSupport/iPhone16,1 17.2.1 (21C66)/Symbols/System/Library/PrivateFrameworks/AttributeGraph.framework" -o ./`
- iOS Simulator's tbd is build by `tbd -p --ignore-weak-def-syms -r -v4 "/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS 15.5.simruntime/Contents/Resources/RuntimeRoot/System/Library/PrivateFrameworks/AttributeGraph.framework" -o ./`
- macOS's tbd is from macOS 12.3 SDK(bundled with Xcode 13.4.1)