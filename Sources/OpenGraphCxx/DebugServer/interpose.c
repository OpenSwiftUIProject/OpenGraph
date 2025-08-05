//
//  interpose.c
//  OpenGraphCxx

#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define DYLD_INTERPOSE(_replacement,_replacee) \
   __attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
            __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

extern bool os_variant_has_internal_diagnostics(const char *subsystem);

bool os_variant_has_internal_diagnostics_og_hook(const char *subsystem) {
    if (strcmp(subsystem, "org.OpenSwiftUIProject.OpenGraph") == 0) {
        return true;
    } else {
        return os_variant_has_internal_diagnostics(subsystem);
    }
}

DYLD_INTERPOSE(os_variant_has_internal_diagnostics_og_hook, os_variant_has_internal_diagnostics)
