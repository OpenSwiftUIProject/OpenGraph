@_exported public import OpenGraph_SPI

// Align the constant define behavior
#if OPENGRAPH_RELEASE_2024
public let OPENGRAPH_RELEASE: Int32 = 2024
#elseif OPENGRAPH_RELEASE_2021
public let OPENGRAPH_RELEASE: Int32 = 2021
#endif
