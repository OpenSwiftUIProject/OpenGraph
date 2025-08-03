//
//  objc_ptr.hpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#ifndef OPENGRAPH_CXX_UTIL_OBJC_PTR_HPP
#define OPENGRAPH_CXX_UTIL_OBJC_PTR_HPP

#include <OpenGraph/OGBase.h>

#if OG_TARGET_OS_DARWIN
#include <objc/objc.h>
#include <objc/runtime.h>

OG_ASSUME_NONNULL_BEGIN

// Redeclare APIs from the Objective-C runtime.
// These functions are not available through public headers, but are guaranteed
// to exist on OS X >= 10.9 and iOS >= 7.0.
OBJC_EXPORT id objc_retain(id obj);
OBJC_EXPORT void objc_release(id obj);

namespace util {

template <typename T> class objc_ptr {
private:
    id _storage;

    static OG_INLINE id to_storage(T obj) { return (id)obj; }
    static OG_INLINE T from_storage(id storage) { return (T)storage; }

public:
    OG_CONSTEXPR objc_ptr() OG_NOEXCEPT : _storage(nil) {}
    OG_CONSTEXPR objc_ptr(std::nullptr_t) OG_NOEXCEPT : _storage(nil) {}

    explicit objc_ptr(T obj) : _storage(to_storage(obj)) {
       if (_storage) {
           objc_retain(_storage);
       }
    }

    ~objc_ptr() {
       if (_storage) {
           objc_release(_storage);
       }
    }

    // MARK: - Copy and move constructors

    objc_ptr(const objc_ptr &other) OG_NOEXCEPT : _storage(other._storage) {
       if (_storage) {
           objc_retain(_storage);
       }
    }

    objc_ptr(objc_ptr &&other) OG_NOEXCEPT : _storage(other._storage) {
       other._storage = nil;
    }

    // MARK: -  Copy and move assignment operators

    objc_ptr &operator=(const objc_ptr &other) OG_NOEXCEPT {
       if (this != &other) {
           if (_storage) {
               objc_release(_storage);
           }
           _storage = other._storage;
           if (_storage) {
               objc_retain(_storage);
           }
       }
       return *this;
    }

    objc_ptr &operator=(objc_ptr &&other) OG_NOEXCEPT {
       if (this != &other) {
           if (_storage) {
               objc_release(_storage);
           }
           _storage = other._storage;
           other._storage = nil;
       }
       return *this;
    }

    // MARK: - Modifiers

    void reset() OG_NOEXCEPT { reset(nil); }

    void reset(T obj = nil) OG_NOEXCEPT {
       if (_storage != obj) {
           if (_storage) {
               objc_release(_storage);
           }
           _storage = to_storage(obj);
           if (_storage) {
               objc_retain(_storage);
           }
       }
    }

    T get() const OG_NOEXCEPT { return from_storage(_storage); }

    explicit operator bool() const OG_NOEXCEPT { return _storage != nil; }
}; /* class objc_ptr */

} /* namespace util */

OG_ASSUME_NONNULL_END

#endif

#endif /* OPENGRAPH_CXX_UTIL_OBJC_PTR_HPP */
