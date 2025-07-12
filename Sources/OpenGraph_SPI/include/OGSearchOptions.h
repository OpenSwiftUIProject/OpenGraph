//
//  OGSearchOptions.h
//  OpenGraph_SPI

#ifndef OGSearchOptions_h
#define OGSearchOptions_h

#include "OGBase.h"

typedef OG_OPTIONS(uint32_t, OGSearchOptions) {
    OGSearchOptionsSearchInputs = 1 << 0,
    OGSearchOptionsSearchOutputs = 1 << 1,
    OGSearchOptionsTraverseGraphContexts = 1 << 2,
};

#endif /* Header_h */
