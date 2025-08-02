//
//  OGSwiftSupport.h
//  OpenGraphCxx

#ifndef OGSwiftSupport_h
#define OGSwiftSupport_h

#if __has_attribute(swift_name)
#define OG_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
#define OG_SWIFT_NAME
#endif

#if __has_attribute(swift_wrapper)
#define OG_SWIFT_STRUCT __attribute__((swift_wrapper(struct)))
#else
#define OG_SWIFT_STRUCT
#endif

#if __has_attribute(swift_private)
#define OG_REFINED_FOR_SWIFT __attribute__((swift_private))
#else
#define OG_REFINED_FOR_SWIFT
#endif

// MARK: - Call Convension

#define OG_SWIFT_CC(CC) OG_SWIFT_CC_##CC
// OG_SWIFT_CC(c) is the C calling convention.
#define OG_SWIFT_CC_c

// OG_SWIFT_CC(swift) is the Swift calling convention.
#if __has_attribute(swiftcall)
#define OG_SWIFT_CC_swift __attribute__((swiftcall))
#define OG_SWIFT_CONTEXT __attribute__((swift_context))
#define OG_SWIFT_ERROR_RESULT __attribute__((swift_error_result))
#define OG_SWIFT_INDIRECT_RESULT __attribute__((swift_indirect_result))
#else
#define OG_SWIFT_CC_swift
#define OG_SWIFT_CONTEXT
#define OG_SWIFT_ERROR_RESULT
#define OG_SWIFT_INDIRECT_RESULT
#endif

#endif /* OGSwiftSupport_h */
