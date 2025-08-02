//
//  OGWeakAttribute.cpp
//  
//
//  Created by Kyle on 2024/2/27.
//

#include <OpenGraphC/OGWeakAttribute.h>

OGWeakAttribute OGCreateWeakAttribute(OGAttribute attribute) {
    // TODO
    return {OGAttributeNil , 0};
}

OGAttribute OGWeakAttributeGetAttribute(OGWeakAttribute weakAttribute) {
    // TODO
    return OGAttributeNil;
}

OGValue OGGraphGetWeakValue(OGWeakAttribute weakAttribute, OGValueOptions options, OGTypeID type) {
    // TODO
    return {nullptr, false};
}
