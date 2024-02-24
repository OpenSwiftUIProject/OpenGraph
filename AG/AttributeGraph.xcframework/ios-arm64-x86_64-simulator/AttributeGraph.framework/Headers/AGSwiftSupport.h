//
//  AGSwiftSupport.h
//
//
//  Created by Kyle on 2024/2/25.
//

#ifndef AGSwiftSupport_h
#define AGSwiftSupport_h

#if __has_attribute(swift_name)
#define AG_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
#define AG_SWIFT_NAME
#endif

#if __has_attribute(swift_wrapper)
#define AG_SWIFT_STRUCT __attribute__((swift_wrapper(struct)))
#else
#define AG_SWIFT_STRUCT
#endif

#if __has_attribute(swift_private)
#define AG_REFINED_FOR_SWIFT __attribute__((swift_private))
#else
#define AG_REFINED_FOR_SWIFT
#endif

// MARK: - Call Convension

#define AG_SWIFT_CC(CC) AG_SWIFT_CC_##CC
// AG_SWIFT_CC(c) is the C calling convention.
#define AG_SWIFT_CC_c

// AG_SWIFT_CC(swift) is the Swift calling convention.
#if __has_attribute(swiftcall)
#define AG_SWIFT_CC_swift __attribute__((swiftcall))
#define AG_SWIFT_CONTEXT __attribute__((swift_context))
#define AG_SWIFT_ERROR_RESULT __attribute__((swift_error_result))
#define AG_SWIFT_INDIRECT_RESULT __attribute__((swift_indirect_result))
#else
#define AG_SWIFT_CC_swift
#define AG_SWIFT_CONTEXT
#define AG_SWIFT_ERROR_RESULT
#define AG_SWIFT_INDIRECT_RESULT
#endif

#endif /* AGSwiftSupport_h */
