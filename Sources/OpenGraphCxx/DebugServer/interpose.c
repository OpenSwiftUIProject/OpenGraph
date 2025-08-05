//
//  interpose.c
//  OpenGraphCxx

#include <OpenGraph/OGBase.h>
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#if OG_TARGET_OS_DARWIN
extern bool os_variant_has_internal_diagnostics(const char *subsystem);
#endif

bool og_variant_has_internal_diagnostics(const char *subsystem) {
    if (strcmp(subsystem, "org.OpenSwiftUIProject.OpenGraph") == 0) {
        return true;
    } else if (strcmp(subsystem, "com.apple.AttributeGraph") == 0) {
        return true;
    } else {
        #if OG_TARGET_OS_DARWIN
        return os_variant_has_internal_diagnostics(subsystem);
        #else
        return false;
        #endif
    }
}

#if OG_TARGET_OS_DARWIN
#define DYLD_INTERPOSE(_replacement,_replacee) \
   __attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
            __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

DYLD_INTERPOSE(og_variant_has_internal_diagnostics, os_variant_has_internal_diagnostics)
#endif
