//
//  OGLog.cpp
//  OpenGraph
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#include "log.hpp"

#if OG_TARGET_OS_DARWIN

namespace OG {
os_log_t misc_log() {
    static os_log_t log = os_log_create("org.OpenSwiftUIProject.OpenGraph", "misc");
    return log;
}
os_log_t error_log() {
    static os_log_t log = os_log_create("org.OpenSwiftUIProject.OpenGraph", "error");
    return log;
}
} /* OG */

#endif /* OG_TARGET_OS_DARWIN */
