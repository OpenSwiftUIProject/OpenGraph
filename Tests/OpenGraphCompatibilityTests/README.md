## OpenSwiftUICompatibilityTests

Test public API of OpenGraph and run it against with AttributeGraph on Apple Platform.

The current supported OS 
- macOS 13 (CI Supported)
- macOS 14 (GitHub Runner not ready)
- iOS 15 ~ 17 on Simulator (CI is not supported)

```swift
#if OPENGRAPH_COMPATIBILITY_TEST
import AttributeGraph
#else
import OpenGraph
#endif
```
