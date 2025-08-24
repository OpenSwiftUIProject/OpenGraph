//
//  OGGraphContext.cpp
//  OpenGraphCxx

#include <OpenGraph/OGGraphContext.h>
#include <OpenGraph/Private/CFRuntime.h>

OGGraphRef OGGraphContextGetGraph(void *context) {
    return reinterpret_cast<OGGraphRef>(reinterpret_cast<uintptr_t>(context) - sizeof(CFRuntimeBase));
}
