//
//  OGBase.h
//  OpenGraph_SPI

#ifndef OGBase_h
#define OGBase_h

#if DEBUG
#define OG_ASSERTION
#else
#undef OG_ASSERTION
#endif

#if __has_attribute(cold)
#define __cold __attribute__((__cold__))
#else
#define __cold
#endif

#if __has_attribute(noreturn)
#define __dead2 __attribute__((__noreturn__))
#else
#define __dead2
#endif

#if defined(__cplusplus)
#define OG_NOEXCEPT noexcept
#else
#define OG_NOEXCEPT
#endif

#if defined(__GNUC__)
#define OG_INLINE __inline__ __attribute__((always_inline))
#elif defined(__cplusplus)
#define OG_INLINE inline
#else
#define OG_INLINE
#endif

#if defined(__cplusplus)
#define OG_CONSTEXPR constexpr
#else
#define OG_CONSTEXPR
#endif

#if __has_include(<ptrcheck.h>) // Fix conflict define issue of the SDK
#include <ptrcheck.h>
#define OG_COUNTED_BY(N) __counted_by(N)
#else
#if !defined(__counted_by)
#if __has_attribute(__counted_by__)
#define __counted_by(N) __attribute__((__counted_by__(N)))
#else
#define __counted_by(N)
#endif
#endif
#define OG_COUNTED_BY(N) __counted_by(N)
#endif

#include "OGSwiftSupport.h"
#include "OGTargetConditionals.h"
#include <CoreFoundation/CoreFoundation.h>
#include <stdbool.h>
#include <stdint.h>

#define OG_ENUM CF_ENUM
#define OG_CLOSED_ENUM CF_CLOSED_ENUM
#define OG_OPTIONS CF_OPTIONS
#define OG_EXTERN_C_BEGIN CF_EXTERN_C_BEGIN
#define OG_EXTERN_C_END CF_EXTERN_C_END
#define OG_ASSUME_NONNULL_BEGIN CF_ASSUME_NONNULL_BEGIN
#define OG_ASSUME_NONNULL_END CF_ASSUME_NONNULL_END
#define OG_IMPLICIT_BRIDGING_ENABLED CF_IMPLICIT_BRIDGING_ENABLED
#define OG_IMPLICIT_BRIDGING_DISABLED CF_IMPLICIT_BRIDGING_DISABLED
#define OG_EXPORT CF_EXPORT
#define OG_BRIDGED_TYPE CF_BRIDGED_TYPE

#if OG_TARGET_OS_DARWIN && __OBJC__
#define OG_OBJC_FOUNDATION 1
#else
#define OG_OBJC_FOUNDATION 0
#endif /* OG_TARGET_OS_DARWIN && __OBJC__ */

#endif /* OGBase_h */
