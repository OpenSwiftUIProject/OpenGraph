//
//  OGLog.hpp
//  
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#ifndef OGLog_hpp
#define OGLog_hpp

#include "OGBase.hpp"
#if TARGET_OS_DARWIN
#include <os/log.h>
#endif /* TARGET_OS_DARWIN */

namespace OG {
#if TARGET_OS_DARWIN
os_log_t misc_log();
os_log_t error_log();
#endif /* TARGET_OS_DARWIN */

void precondition_failure(const char *format, ...) __cold __dead2;
void non_fatal_precondition_failure(const char *format, ...);
}
#endif /* OGLog_hpp */
