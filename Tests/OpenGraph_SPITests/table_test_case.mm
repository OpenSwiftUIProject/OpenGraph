//
//  table_test_case.mm
//  OpenGraph_SPITests

#include <XCTest/XCTest.h>
#include "Data/table.hpp"

using namespace OG;

@interface TableTestCase : XCTestCase
@end

@implementation TableTestCase

- (void)setUp {
    [super setUp];
    data::table::ensure_shared();
}

@end
