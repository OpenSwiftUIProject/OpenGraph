//
//  OGLog.cpp
//  OpenGraph
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#include "log.hpp"

#if TARGET_OS_DARWIN
#include <stdio.h>
#include <stdlib.h>

namespace OG {
os_log_t misc_log() {
    static os_log_t log = os_log_create("org.openswiftuiproject.opengraph", "misc");
    return log;
}
os_log_t error_log() {
    static os_log_t log = os_log_create("org.openswiftuiproject.opengraph", "error");
    return log;
}
} /* OG */

#endif /* TARGET_OS_DARWIN */
