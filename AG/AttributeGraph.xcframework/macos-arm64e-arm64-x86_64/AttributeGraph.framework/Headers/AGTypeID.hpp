//
//  AGTypeID.hpp
//  
//
//  Created by Kyle on 2024/1/8.
//

#ifndef AGTypeID_hpp
#define AGTypeID_hpp

#include <CoreFoundation/CoreFoundation.h>
#include "AGSwiftMetadata.hpp"

typedef const AGSwiftMetadata *AGTypeID __attribute__((swift_wrapper(struct)));

#endif /* AGTypeID_hpp */
