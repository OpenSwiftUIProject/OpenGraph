//
//  OGTreeElement.cpp
//  OpenGraphCxx

#include <OpenGraph/OGTreeElement.h>

OGTypeID OGTreeElementGetType(OGTreeElement tree_element) {
    // TODO
    return nullptr;
}

OGAttribute OGTreeElementGetValue(OGTreeElement tree_element) {
    // TODO
    return OGAttributeNil;
}

uint32_t OGTreeElementGetFlags(OGTreeElement tree_element) {
    // TODO
    return 0;
}

OGTreeElement OGTreeElementGetParent(OGTreeElement tree_element) {
    // TODO
    return nullptr;
}

OGTreeElementValueIterator OGTreeElementMakeValueIterator(OGTreeElement tree_element) {
    // TODO
    return {0, 0};
}

OGTreeValue OGTreeElementGetNextValue(OGTreeElementValueIterator *iter) {
    // TODO
    return nullptr;
}

OGTreeElementNodeIterator OGTreeElementMakeNodeIterator(OGTreeElement tree_element) {
    // TODO
    return {0, 0};
}

OGAttribute OGTreeElementGetNextNode(OGTreeElementNodeIterator *iter) {
    // TODO
    return OGAttributeNil;
}

OGTreeElementChildIterator OGTreeElementMakeChildIterator(OGTreeElement tree_element) {
    // TODO
    return {0, 0, 0};
}

OGTreeElement OGTreeElementGetNextChild(OGTreeElementChildIterator *iter) {
    // TODO
    return 0;
}
