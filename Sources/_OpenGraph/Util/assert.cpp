//
//  assert.cpp
//  
//
//  Created by Kyle on 2024/1/21.
//

#include "assert.hpp"
#include "log.hpp"

char* error_message = nullptr;

namespace OG {
void precondition_failure(const char *format, ...) {
    char* s = nullptr;
    va_list va;
    va_start(va, format);
    vasprintf(&s, format, va);
    va_end(va);
    if (s != nullptr) {
        #if TARGET_OS_DARWIN
        os_log_error(error_log(), "precondition failure: %s", s);
        #endif /* TARGET_OS_DARWIN */
        // 2023 release addition
        // OG::Graph::trace_assertion_failure(true, "precondition failure: %s", s)
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
        #if TARGET_OS_DARWIN
        os_log_fault(error_log(), "precondition failure: %s", s);
        #endif /* TARGET_OS_DARWIN */
        free(s);
    }
    return;
}
} /* OG */
