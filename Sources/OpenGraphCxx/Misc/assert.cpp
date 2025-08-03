//
//  assert.cpp
//  OpenGraphCxx

#include <OpenGraphCxx/Misc/assert.hpp>
#include <OpenGraphCxx/Misc/log.hpp>

#include <stdio.h>
#include <stdlib.h>

char* error_message = nullptr;

namespace OG {
void precondition_failure(const char *format, ...) {
    char* s = nullptr;
    va_list va;
    va_start(va, format);
    vasprintf(&s, format, va);
    va_end(va);
    if (s != nullptr) {
        #if OG_TARGET_OS_DARWIN
        os_log_error(error_log(), "precondition failure: %s", s);
        #endif /* OG_TARGET_OS_DARWIN */
        #if OG_TARGET_RELEASE >= OG_RELEASE_2023
        // OG::Graph::trace_assertion_failure(true, "precondition failure: %s", s)
        #endif
        if (error_message == nullptr) {
            asprintf(&error_message, "OpenGraph precondition failure: %s.\n", s);
        }
        free(s);
    }
    abort();
}

void non_fatal_precondition_failure(const char *format, ...) {
    char* s = nullptr;
    va_list va;
    va_start(va, format);
    vasprintf(&s, format, va);
    va_end(va);
    if (s != nullptr) {
        #if OG_TARGET_OS_DARWIN
        os_log_fault(error_log(), "precondition failure: %s", s);
        #endif /* OG_TARGET_OS_DARWIN */
        free(s);
    }
    return;
}
} /* OG */
