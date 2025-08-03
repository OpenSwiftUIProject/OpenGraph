//
//  cf_ptr.hpp
//  OpenGraphCxx
//
//  Status: Complete
//  Modified based Compute code

#ifndef OPENGRAPH_CXX_UTIL_CF_PTR_HPP
#define OPENGRAPH_CXX_UTIL_CF_PTR_HPP

#include <OpenGraph/OGBase.h>
#include <CoreFoundation/CoreFoundation.h>

OG_ASSUME_NONNULL_BEGIN

namespace util {

template <typename T> class cf_ptr {
private:
    CFTypeRef _storage;

    static OG_INLINE CFTypeRef to_storage(T ref) { return (CFTypeRef)(ref); }
    static OG_INLINE T from_storage(CFTypeRef storage) { return (T)storage; }

public:
    OG_CONSTEXPR cf_ptr() OG_NOEXCEPT : _storage(nullptr) {}
    OG_CONSTEXPR cf_ptr(std::nullptr_t) OG_NOEXCEPT : _storage(nullptr) {}

    explicit cf_ptr(T ref) : _storage(to_storage(ref)) {
       if (_storage) {
           CFRetain(_storage);
       }
    }

    ~cf_ptr() {
       if (_storage) {
           CFRelease(_storage);
       }
    }

    // Copy and move constructors

    cf_ptr(const cf_ptr &other) OG_NOEXCEPT : _storage(other._storage) {
       if (_storage) {
           CFRetain(_storage);
       }
    };

    cf_ptr(cf_ptr &&other) OG_NOEXCEPT : _storage(std::exchange(other._storage, nullptr)) {};

    // Copy and move assignment operators

    cf_ptr &operator=(const cf_ptr &other) OG_NOEXCEPT {
       if (this != &other) {
           if (_storage) {
               CFRelease(_storage);
           }
           _storage = other._storage;
           if (_storage) {
               CFRetain(_storage);
           }
       }
       return *this;
    };

    cf_ptr &operator=(cf_ptr &&other) OG_NOEXCEPT {
       if (this != &other) {
           if (_storage) {
               CFRelease(_storage);
           }
           _storage = other._storage;
           other._storage = nullptr;
       }
       return *this;
    }

    // Modifiers

    void reset() OG_NOEXCEPT { reset(nullptr); }

    void reset(T ref = nullptr) OG_NOEXCEPT {
       if (_storage != ref) {
           if (_storage) {
               CFRelease(_storage);
           }
           _storage = to_storage(ref);
           if (_storage) {
               CFRetain(_storage);
           }
       }
    }

    // Observers

    T get() const OG_NOEXCEPT { return from_storage(_storage); };

    explicit operator bool() const OG_NOEXCEPT { return _storage != nullptr; }
}; /* class cf_ptr */

using cf_data_ptr = cf_ptr<CFDataRef>;
using cf_mutable_data_ptr = cf_ptr<CFMutableDataRef>;

} /* namespace util */

OG_ASSUME_NONNULL_END

#endif /* OPENGRAPH_CXX_UTIL_CF_PTR_HPP */
