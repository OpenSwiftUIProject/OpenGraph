//
//  OGComparison.h
//  OpenGraph_SPI
//
//  Audited for 6.5.4
//  Status: Complete

//
//  Modified based on Compute project: https://github.com/jcmosc/Compute/blob/main/Sources/ComputeCxx/Comparison/AGComparison.h
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

#ifndef OGComparison_h
#define OGComparison_h

#include "OGBase.h"
#include "OGTypeID.h"

OG_ASSUME_NONNULL_BEGIN

OG_EXTERN_C_BEGIN

typedef struct OGFieldRange {
    size_t offset;
    size_t size;
} OGFieldRange OG_SWIFT_STRUCT OG_SWIFT_NAME(FieldRange);

typedef const void *OGComparisonState OG_SWIFT_STRUCT OG_SWIFT_NAME(ComparisonState);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void *OGComparisonStateGetDestination(OGComparisonState state) OG_SWIFT_NAME(getter:OGComparisonState.destination(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
const void *OGComparisonStateGetSource(OGComparisonState state) OG_SWIFT_NAME(getter:OGComparisonState.source(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGFieldRange OGComparisonStateGetFieldRange(OGComparisonState state) OG_SWIFT_NAME(getter:OGComparisonState.fieldRange(self:));

OG_EXPORT
OG_REFINED_FOR_SWIFT
OGTypeID OGComparisonStateGetFieldType(OGComparisonState state) OG_SWIFT_NAME(getter:OGComparisonState.fieldType(self:));

typedef OG_ENUM(uint8_t, OGComparisonMode) {
    OGComparisonModeBitwise = 0,
    OGComparisonModeIndirect = 1,
    OGComparisonModeEquatableUnlessPOD = 2,
    OGComparisonModeEquatableAlways = 3,
} OG_SWIFT_NAME(ComparisonMode);

typedef OG_OPTIONS(uint32_t, OGComparisonOptions) {
    OGComparisonOptionsComparisonModeBitwise = 0,
    OGComparisonOptionsComparisonModeIndirect = 1,
    OGComparisonOptionsComparisonModeEquatableUnlessPOD = 2,
    OGComparisonOptionsComparisonModeEquatableAlways = 3,
    OGComparisonOptionsComparisonModeMask = 0xff,

    OGComparisonOptionsCopyOnWrite = 1 << 8,
    OGComparisonOptionsFetchLayoutsSynchronously = 1 << 9,
    OGComparisonOptionsReportFailures = 1ul << 31, // -1 signed int
} OG_SWIFT_NAME(ComparisonOptions);

OG_EXPORT
OG_REFINED_FOR_SWIFT
bool OGCompareValues(const void *lhs,
                     const void *rhs,
                     OGTypeID type_id,
                     OGComparisonOptions options);

OG_EXPORT
OG_REFINED_FOR_SWIFT
const unsigned char *_Nullable OGPrefetchCompareValues(OGTypeID type_id,
                                                       OGComparisonOptions options,
                                                       uint32_t priority);

OG_EXPORT
OG_REFINED_FOR_SWIFT
void OGOverrideComparisonForTypeDescriptor(void *descriptor, OGComparisonMode mode);

OG_EXTERN_C_END

OG_ASSUME_NONNULL_END

#endif /* OGComparison_h */
