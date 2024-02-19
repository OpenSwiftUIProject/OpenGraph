//
//  AGValue.h
//
//
//  Created by Kyle on 2024/2/19.
//

#ifndef AGValue_h
#define AGValue_h

#include "AGBase.h"

AG_ASSUME_NONNULL_BEGIN

typedef struct AGValue {
    const void* value;
    const bool changed;
} AGValue;

AG_ASSUME_NONNULL_END

#endif /* AGValue_h */
