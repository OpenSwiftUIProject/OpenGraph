//
//  table.hpp
//  OpenGraph_SPI

#ifndef table_hpp
#define table_hpp

#include "OGBase.h"

namespace OG {
namespace data {
class zone;
class page;

class table {
    
public:
    static table &ensure_shared();
    static table &shared();
    
    table();
    
    void print() const;
};

} /* data */
} /* OG */

#endif /* table_hpp */
