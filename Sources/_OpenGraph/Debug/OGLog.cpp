//
//  OGLog.cpp
//  OpenGraph
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#include "OGLog.hpp"

#if TARGET_OS_DARWIN
#include <stdio.h>
#include <stdlib.h>

char* error_message = nullptr;

namespace OG {
#if TARGET_OS_DARWIN
os_log_t misc_log() {
    static os_log_t log = os_log_create("org.openswiftuiproject.opengraph", "misc");
    return log;
}
os_log_t error_log() {
    static os_log_t log = os_log_create("org.openswiftuiproject.opengraph", "error");
    return log;
}
#endif /* TARGET_OS_DARWIN */

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
}
#endif /* TARGET_OS_DARWIN */
