//
//  OGLog.hpp
//  
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#ifndef OGLog_hpp
#define OGLog_hpp

#include <OpenFoundation/OpenFoundation.h>
#if TARGET_OS_DARWIN
#include <os/log.h>

namespace OG {
os_log_t misc_log();
os_log_t error_log();

void precondition_failure(const char *format, ...);
void non_fatal_precondition_failure(const char *format, ...);
}
#endif /* TARGET_OS_DARWIN */
#endif /* OGLog_hpp */
