//
//  AGBase.hpp
//
//
//  Created by Kyle on 2024/1/16.
//

#ifndef AGBase_h
#define AGBase_h

#if DEBUG
#define AG_ASSERTION
#else
#undef AG_ASSERTION
#endif

#if __has_attribute(cold)
#define __cold          __attribute__((__cold__))
#else
#define __cold
#endif
#define __dead2         __attribute__((__noreturn__))

#if defined(__cplusplus)
#define AG_NOEXCEPT noexcept
#else
#define AG_NOEXCEPT
#endif

#if defined(__cplusplus)
#define AG_INLINE inline
#else
#define AG_INLINE
#endif

#if defined(__cplusplus)
#define AG_CONSTEXPR constexpr
#else
#define AG_CONSTEXPR
#endif

#define AG_SWIFT_STRUCT __attribute__((swift_wrapper(struct)))

#include <CoreFoundation/CoreFoundation.h>
#include <TargetConditionals.h>
#define AG_OPTIONS CF_OPTIONS
#define AG_EXTERN_C_BEGIN CF_EXTERN_C_BEGIN
#define AG_EXTERN_C_END CF_EXTERN_C_END
#define AG_ASSUME_NONNULL_BEGIN CF_ASSUME_NONNULL_BEGIN
#define AG_ASSUME_NONNULL_END CF_ASSUME_NONNULL_END
#define AG_EXPORT CF_EXPORT
#define AG_REFINED_FOR_SWIFT CF_REFINED_FOR_SWIFT
#define AG_SWIFT_NAME CF_SWIFT_NAME
#endif /* AGBase_h */
