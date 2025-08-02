//
//  OGGraphContext.cpp
//  
//
//  Created by Kyle on 2024/2/16.
//

#include "OGGraphContext.h"
#include <OpenGraphCxx/Private/CFRuntime.h>

OGGraphRef OGGraphContextGetGraph(OGGraphContextRef context) {
    return reinterpret_cast<OGGraphRef>(reinterpret_cast<uintptr_t>(context) - sizeof(CFRuntimeBase));
}
