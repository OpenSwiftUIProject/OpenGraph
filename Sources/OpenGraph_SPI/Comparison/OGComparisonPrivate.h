//
//  OGComparisonPrivate.h
//  OpenGraph_SPI
//
//  Audited for 6.5.4
//  Status: Complete
//
//  Modified based on Compute project: https://github.com/jcmosc/Compute/blob/main/Sources/ComputeCxx/Comparison/AGComparison-Private.h
//  Copyright (c) 2025 James Moschou
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMOGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#ifndef OGComparisonPrivate_h
#define OGComparisonPrivate_h

#include "OGBase.h"
#include "OGComparison.h"
#include "OGTypeID.h"

OG_ASSUME_NONNULL_BEGIN

OG_EXTERN_C_BEGIN

typedef struct OGComparisonStateStorage {
    const void *destination;
    const void *source;
    OGFieldRange field_range;
    OGTypeID field_type;
} OGComparisonStateStorage;

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGComparisonPrivate_h */

