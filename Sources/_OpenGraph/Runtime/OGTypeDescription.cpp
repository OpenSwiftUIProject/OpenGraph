//
//  OGTypeDescription.cpp
//  
//
//  Created by Kyle on 2024/1/24.
//

#include "OGTypeDescription.h"

#if OG_TARGET_OS_DARWIN
CFStringRef OGTypeDescription(OGTypeID id) {
    CFMutableStringRef ref = CFStringCreateMutable(CFAllocatorGetDefault(), 0);
    // OG::swift::metadata::append_description(__CFString*) const
    // cast id into metadata and call append_description
    return ref;
}
#endif /* OG_TARGET_OS_DARWIN */
