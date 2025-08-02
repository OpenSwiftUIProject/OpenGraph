//
//  ClosureFunction.hpp
//  OpenGraphCxx

#ifndef ClosureFunction_hpp
#define ClosureFunction_hpp

#include <OpenGraph/OGBase.h>
#include <functional>

OG_ASSUME_NONNULL_BEGIN

namespace OG {
template <typename ReturnType, typename... Args>
class ClosureFunction final {
public:
    typedef const void  * _Nullable Context;
    typedef const ReturnType (* _Nullable Callable)(Context OG_SWIFT_CONTEXT, Args...) OG_SWIFT_CC(swift);

    OG_INLINE OG_CONSTEXPR
    ClosureFunction(Callable function, Context context) OG_NOEXCEPT :
    _function(function),
    _context(context) {
    }
    
    OG_INLINE OG_CONSTEXPR
    ClosureFunction(std::nullptr_t) OG_NOEXCEPT :
    _function(nullptr),
    _context(nullptr) {
    }
    
    OG_INLINE
    ~ClosureFunction() noexcept {
    }
    
    OG_INLINE OG_CONSTEXPR
    ClosureFunction(const ClosureFunction &value) OG_NOEXCEPT :
    _function(value._function),
    _context(value._context) {
    }
    
    OG_INLINE OG_CONSTEXPR
    explicit operator bool() const OG_NOEXCEPT {
        return _function != nullptr;
    }
    
    OG_INLINE OG_CONSTEXPR
    bool operator==(const ClosureFunction &rhs) const OG_NOEXCEPT {
        return _function == rhs._function && _context == rhs._context;
    }
    
    OG_INLINE OG_CONSTEXPR
    bool operator==(std::nullptr_t) const OG_NOEXCEPT {
        return _function == nullptr;
    }
    
    OG_INLINE OG_CONSTEXPR
    bool operator!=(std::nullptr_t) const OG_NOEXCEPT {
        return _function != nullptr;
    }
    
    OG_INLINE OG_CONSTEXPR
    const ReturnType operator()(Args... args) const OG_NOEXCEPT {
        return _function(_context, std::forward<Args>(args)...);
    }
private:
    Callable _function;
    Context _context;
};
}

OG_ASSUME_NONNULL_END

#endif /* ClosureFunction_hpp */
