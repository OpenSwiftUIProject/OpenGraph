//
//  OGTypeDescription.cpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#include "OGTypeDescription.hpp"

#if TARGET_OS_DARWIN
CFStringRef OGTypeDescription(OGTypeID id) {
    CFMutableStringRef ref = CFStringCreateMutable(CFAllocatorGetDefault(), 0);
    // OG::swift::metadata::append_description(__CFString*) const
    // cast id into metadata and call append_description
    return ref;
}
#endif /* TARGET_OS_DARWIN */
