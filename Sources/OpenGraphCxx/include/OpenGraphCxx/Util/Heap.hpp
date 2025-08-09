//
//  Heap.hpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#ifndef OPENGRAPH_CXX_UTIL_HEAP_HPP
#define OPENGRAPH_CXX_UTIL_HEAP_HPP

#include <OpenGraph/OGBase.h>
#include <swift/bridging>

OG_ASSUME_NONNULL_BEGIN

namespace util {

class Heap {
protected:
    typedef struct Node {
        struct Node *next;
        void *buffer;
    } Node;

    size_t _increment;
    Node *_node;
    char *_free_start;
    size_t _capacity;

    void *alloc_(size_t arg1);

public:
    static constexpr size_t minimum_increment = 0x400;

    static Heap *create(char *_Nullable start, size_t capacity, size_t increment);
    static void destroy(Heap *value);

    Heap(char *_Nullable start, size_t capacity, size_t increment);
    ~Heap();

    // non-copyable
    Heap(const Heap &) = delete;
    Heap &operator=(const Heap &) = delete;

    // non-movable
    Heap(Heap &&) = delete;
    Heap &operator=(Heap &&) = delete;

    template <typename T> inline T *_Nonnull alloc(size_t count = 1) {
        return static_cast<T *>(alloc_(sizeof(T) * count));
    };
    void reset(char *_Nullable start, size_t capacity);

    // Debugging

    size_t num_nodes() const;
    size_t increment() const { return _increment; }
    size_t capacity() const { return _capacity; }

    void print() const;

    #ifdef SWIFT_TESTING
    uint64_t *alloc_uint64_t(size_t count = 1) { return alloc<uint64_t>(count); }
    #endif

} SWIFT_UNSAFE_REFERENCE;

template <unsigned int _inline_size> class InlineHeap : public Heap {
private:
    char _inline_buffer[_inline_size] = {};

public:
    InlineHeap() : Heap(_inline_buffer, _inline_size, 0) {}
};

} /* namespace util */

OG_ASSUME_NONNULL_END

#endif /* OPENGRAPH_CXX_UTIL_HEAP_HPP */
