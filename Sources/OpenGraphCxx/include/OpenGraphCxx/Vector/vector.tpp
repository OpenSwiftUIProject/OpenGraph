//
//  vector.tpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#include <OpenGraphCxx/Vector/vector.hpp>
#include <OpenGraphCxx/Misc/assert.hpp>

#include <algorithm>
#if OG_TARGET_OS_DARWIN
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif /* OG_TARGET_OS_DARWIN */
#include <memory>
#include <cassert>

namespace OG {

#pragma mark - Base implementation

namespace details {

template <typename size_type, unsigned int element_size_bytes>
    requires std::unsigned_integral<size_type>
void *realloc_vector(void *buffer, void *stack_buffer, size_type stack_size, size_type *size,
                     size_type preferred_new_size) {
    // copy data from heap buffer buffer into stack buffer if possible
    if (preferred_new_size <= stack_size) {
        if (buffer) {
            memcpy(stack_buffer, buffer, preferred_new_size * element_size_bytes);
            free(buffer);
            *size = stack_size;
        }
        return nullptr;
    }

    #if OG_TARGET_OS_DARWIN
    size_t new_size_bytes = malloc_good_size(preferred_new_size * element_size_bytes);
    #else
    size_t new_size_bytes = malloc_good_size(preferred_new_size * element_size_bytes);
    #endif
    size_type new_size = new_size_bytes / element_size_bytes;
    if (new_size == *size) {
        // nothing to do
        return buffer;
    }

    void *new_buffer = realloc(buffer, new_size_bytes);
    if (!new_buffer) {
        precondition_failure("allocation failure");
    }

    // copy data from stack buffer into heap buffer
    if (!buffer) {
        memcpy(new_buffer, stack_buffer, (*size) * element_size_bytes);
    }

    *size = new_size;
    return new_buffer;
}

} /* namespace details */

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
vector<T, _stack_size, size_type>::~vector() {
    for (auto i = 0; i < _size; i++) {
        data()[i].~T();
    }
    if (_buffer) {
        free(_buffer);
    }
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::reserve_slow(size_type new_cap) {
    size_type effective_new_cap = std::max(capacity() * 1.5, new_cap * 1.0);
    _buffer = reinterpret_cast<T *>(details::realloc_vector<size_type, sizeof(T)>(_buffer, _stack_buffer, _stack_size,
                                                                                  &_capacity, effective_new_cap));
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::reserve(size_type new_cap) {
    if (new_cap <= capacity()) {
        return;
    }
    reserve_slow(new_cap);
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::shrink_to_fit() {
    if (capacity() > _size) {
        _buffer = reinterpret_cast<T *>(
            details::realloc_vector<size_type, sizeof(T)>(_buffer, _stack_buffer, _stack_size, &_capacity, _size));
    }
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::clear() {
    for (auto i = 0; i < _size; i++) {
        data()[i].~T();
    }
    _size = 0;
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::push_back(const T &value) {
    reserve(_size + 1);
    new (&data()[_size]) value_type(value);
    _size += 1;
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::push_back(T &&value) {
    reserve(_size + 1);
    new (&data()[_size]) value_type(std::move(value));
    _size += 1;
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::pop_back() {
    assert(size() > 0);
    data()[_size - 1].~T();
    _size -= 1;
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::resize(size_type count) {
    reserve(count);
    if (count < _size) {
        for (auto i = count; i < _size; i++) {
            data()[i].~T();
        }
    } else if (count > _size) {
        for (auto i = _size; i < count; i++) {
            new (this[i]) value_type();
        }
    }
    _size = count;
}

template <typename T, unsigned int _stack_size, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, _stack_size, size_type>::resize(size_type count, const value_type &value) {
    reserve(count);
    if (count < _size) {
        for (auto i = count; i < _size; i++) {
            data()[i].~T();
        }
    } else if (count > _size) {
        for (auto i = _size; i < count; i++) {
            new (this[i]) value_type(value);
        }
    }
    _size = count;
}

#pragma mark - Specialization for empty stack buffer

namespace details {

template <typename size_type, size_t element_size>
    requires std::unsigned_integral<size_type>
void *realloc_vector(void *buffer, size_type *size, size_type preferred_new_size) {
    if (preferred_new_size == 0) {
        *size = 0;
        free(buffer);
        return nullptr;
    }

    #if OG_TARGET_OS_DARWIN
    size_t new_size_bytes = malloc_good_size(preferred_new_size * element_size);
    #else
    size_t new_size_bytes = preferred_new_size * element_size;
    #endif
    size_type new_size = (size_type)(new_size_bytes / element_size);
    if (new_size == *size) {
        // nothing to do
        return buffer;
    }

    void *new_buffer = realloc(buffer, new_size_bytes);
    if (!new_buffer) {
        precondition_failure("allocation failure");
    }
    *size = new_size;
    return new_buffer;
}

} /* namespace details */

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
vector<T, 0, size_type>::~vector() {
    for (auto i = 0; i < _size; i++) {
        _buffer[i].~T();
    }
    if (_buffer) {
        free(_buffer);
    }
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::reserve_slow(size_type new_cap) {
    size_type effective_new_cap = std::max(capacity() * 1.5, new_cap * 1.0);
    _buffer =
        reinterpret_cast<T *>(details::realloc_vector<size_type, sizeof(T)>(_buffer, &_capacity, effective_new_cap));
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::reserve(size_type new_cap) {
    if (new_cap <= capacity()) {
        return;
    }
    reserve_slow(new_cap);
}

template <typename T, typename size_type>
requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::shrink_to_fit() {
    if (capacity() > size()) {
        _buffer =
        reinterpret_cast<T *>(details::realloc_vector<size_type, sizeof(T)>(_buffer, &_capacity, 0));
    }
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::clear() {
    for (auto i = 0; i < _size; i++) {
        data()[i].~T();
    }
    _size = 0;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::push_back(const T &value) {
    reserve(_size + 1);
    new (&_buffer[_size]) value_type(value);
    _size += 1;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::push_back(T &&value) {
    reserve(_size + 1);
    new (&_buffer[_size]) value_type(std::move(value));
    _size += 1;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::pop_back() {
    assert(size() > 0);
    data()[_size - 1].~T();
    _size -= 1;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::resize(size_type count) {
    reserve(count);
    if (count < _size) {
        for (auto i = count; i < _size; i++) {
            data()[i].~T();
        }
    } else if (count > _size) {
        for (auto i = _size; i < count; i++) {
            new (this[i]) value_type();
        }
    }
    _size = count;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<T, 0, size_type>::resize(size_type count, const value_type &value) {
    reserve(count);
    if (count < _size) {
        for (auto i = count; i < _size; i++) {
            data()[i].~T();
        }
    } else if (count > _size) {
        for (auto i = _size; i < count; i++) {
            new (this[i]) value_type(value);
        }
    }
    _size = count;
}

#pragma mark - Specialization for unique_ptr

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
vector<std::unique_ptr<T>, 0, size_type>::~vector() {
    clear();
    if (_buffer) {
        free(_buffer);
        _buffer = nullptr;
    }
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<std::unique_ptr<T>, 0, size_type>::clear() {
    for (size_type i = 0; i < _size; ++i) {
        _buffer[i].reset();
        _buffer[i].~unique_ptr();
    }
    _size = 0;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<std::unique_ptr<T>, 0, size_type>::reserve_slow(size_type new_cap) {
    if (new_cap <= _capacity) {
        return;
    }

    size_type actual_new_cap = std::max(new_cap, _capacity * 2);
    std::unique_ptr<T> *new_buffer = (std::unique_ptr<T> *)malloc(actual_new_cap * sizeof(std::unique_ptr<T>));
    if (!new_buffer) {
        return;
    }

    for (size_type i = 0; i < _size; ++i) {
        new (&new_buffer[i]) std::unique_ptr<T>(std::move(_buffer[i]));
        _buffer[i].~unique_ptr();
    }

    if (_buffer) {
        free(_buffer);
    }

    _buffer = new_buffer;
    _capacity = actual_new_cap;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<std::unique_ptr<T>, 0, size_type>::reserve(size_type new_cap) {
    if (new_cap > _capacity) {
        reserve_slow(new_cap);
    }
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
OG_INLINE void vector<std::unique_ptr<T>, 0, size_type>::push_back(std::unique_ptr<T> &&value) {
    reserve(_size + 1);
    new (&_buffer[_size]) std::unique_ptr<T>(std::move(value));
    ++_size;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
OG_INLINE void vector<std::unique_ptr<T>, 0, size_type>::pop_back() {
    assert(_size > 0);
    _buffer[_size - 1].reset();
    _buffer[_size - 1].~unique_ptr();
    --_size;
}

template <typename T, typename size_type>
    requires std::unsigned_integral<size_type>
void vector<std::unique_ptr<T>, 0, size_type>::resize(size_type count) {
    reserve(count);
    if (count < _size) {
        for (auto i = count; i < _size; i++) {
            _buffer[i].reset();
            _buffer[i].~unique_ptr();
        }
    } else if (count > _size) {
        for (auto i = _size; i < count; i++) {
            new (&_buffer[i]) std::unique_ptr<T>();
        }
    }
    _size = count;
}

} /* OG */
