//
//  OGWeakAttribute.cpp
//  OpenGraphCxx

#include <OpenGraph/OGWeakAttribute.h>

OGWeakAttribute OGCreateWeakAttribute(OGAttribute attribute) {
    // TODO
    return {OGAttributeNil , 0};
}

OGAttribute OGWeakAttributeGetAttribute(OGWeakAttribute weakAttribute) {
    // TODO
    return OGAttributeNil;
}

OGWeakValue OGGraphGetWeakValue(OGWeakAttribute weakAttribute, OGValueOptions options, OGTypeID type) {
    // TODO
    return {nullptr, false};
}
