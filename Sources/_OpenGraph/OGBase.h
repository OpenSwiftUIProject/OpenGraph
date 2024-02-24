//
//  OGBase.h
//
//
//  Created by Kyle on 2024/1/16.
//

#ifndef OGBase_h
#define OGBase_h

#if DEBUG
#define OG_ASSERTION
#else
#undef OG_ASSERTION
#endif

#if __has_attribute(cold)
#define __cold          __attribute__((__cold__))
#else
#define __cold
#endif
#define __dead2         __attribute__((__noreturn__))

#if defined(__cplusplus)
#define OG_NOEXCEPT noexcept
#else
#define OG_NOEXCEPT
#endif

#if defined(__cplusplus)
#define OG_INLINE inline
#else
#define OG_INLINE
#endif

#if defined(__cplusplus)
#define OG_CONSTEXPR constexpr
#else
#define OG_CONSTEXPR
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <stdint.h>
#include <stdbool.h>
#include "OGTargetConditionals.h"
#include "OGSwiftSupport.h"

#define OG_OPTIONS CF_OPTIONS
#define OG_EXTERN_C_BEGIN CF_EXTERN_C_BEGIN
#define OG_EXTERN_C_END CF_EXTERN_C_END
#define OG_ASSUME_NONNULL_BEGIN CF_ASSUME_NONNULL_BEGIN
#define OG_ASSUME_NONNULL_END CF_ASSUME_NONNULL_END
#define OG_EXPORT CF_EXPORT
#define OG_BRIDGED_TYPE CF_BRIDGED_TYPE

#if OG_TARGET_OS_DARWIN && __OBJC__
#define OG_OBJC_FOUNDATION 1
#else
#define OG_OBJC_FOUNDATION 0
#endif /* OG_TARGET_OS_DARWIN && __OBJC__ */

#endif /* OGBase_h */
