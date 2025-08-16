//
//  Heap.cpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#include <OpenGraphCxx/Util/Heap.hpp>
#include <algorithm>

namespace util {

constexpr size_t default_increment = 0x2000;

Heap *Heap::create(char *_Nullable start, size_t capacity, size_t increment) {
    return new Heap(start, capacity, increment);
}

void Heap::destroy(Heap *value) { delete value; }

Heap::Heap(char *start, size_t capacity, size_t increment) {
    // enforce minimum but treat 0 as the default
    size_t effective_increment = increment > 0 ? std::max(increment, minimum_increment) : default_increment;

    _increment = effective_increment;
    _node = nullptr;
    reset(start, capacity);
};

util::Heap::~Heap() { reset(nullptr, 0); }

void *util::Heap::alloc_(size_t size) {
    if (_capacity >= size) {
        char *result = _free_start;
        _free_start += size;
        _capacity -= size;
        return result;
    }

    if (size <= minimum_increment) {
        int64_t increment = _increment;
        char *buffer = static_cast<char *>(malloc(increment));

        _free_start = buffer;
        _capacity = increment;

        Node *node = alloc<Node>();

        node->next = _node;
        node->buffer = buffer;
        _node = node;

        char *result = _free_start;
        _free_start += size;
        _capacity -= size;
        return result;
    }

    Node *node = alloc<Node>();
    void *result = malloc(size);
    if (result) {
        node->next = _node;
        node->buffer = result;
        _node = node;
    }
    return result;
}

void util::Heap::reset(char *_Nullable start, size_t capacity) {
    while (_node) {
        void *buffer = _node->buffer;
        _node = _node->next;
        free(buffer);
    }

    constexpr uintptr_t alignment_mask = sizeof(char *) - 1;
    char *aligned_start = (char *)(((uintptr_t)start + alignment_mask) & ~alignment_mask);

    bool prealigned = ((uintptr_t)start & alignment_mask) == 0;
    _free_start = prealigned ? start : aligned_start;
    _capacity = capacity + (start - aligned_start);
}

size_t util::Heap::num_nodes() const {
    size_t count = 0;
    for (Node *node = _node; node != nullptr; node = node->next) {
        count += 1;
    }
    return count;
}

void util::Heap::print() const {
    fprintf(stdout, "Nodes\n");
    for (Node *node = _node; node != nullptr; node = node->next) {
        fprintf(stdout, "address=%-16p; buffer=%-16p; next=%-16p\n", node, node->buffer, node->next);
    }
}

}; /* namespace util */
