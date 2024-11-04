//
//  OGUniqueID.c
//
//
//  Created by Kyle on 2023/10/9.
//

#include "OGUniqueID.h"
#include <stdatomic.h>

OGUniqueID OGMakeUniqueID(void) {
    // Initial value is 1
    static atomic_llong counter = 1;
    return counter++;
}
