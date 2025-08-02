//
//  log.hpp
//
//
//  Created by Kyle on 2024/1/12.
//  Audited for 2021 Release

#ifndef log_hpp
#define log_hpp

#include <OpenGraph/OGBase.h>

#if OG_TARGET_OS_DARWIN

#include <os/log.h>

namespace OG {
os_log_t misc_log();
os_log_t error_log();
} /* OG */

#endif /* OG_TARGET_OS_DARWIN */

#endif /* log_hpp */
