#pragma once

#include <cassert>
#include <cstdint>
#include <memory>

#include "PlatformDetection.hpp"

namespace BillyEngine {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
using f64 = double;

using std::size_t;

#define BE_STRINGIFY(x) #x

#define BE_BIT(x) (1 << x)

#define BE_NON_COPY_CONSTRUCTIBLE(className)    \
    className(const className& other) = delete; \
    className& operator=(const className&) = delete;

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#ifdef BE_PLATFORM_WINDOWS
    #define BE_FUNC_SIG __FUNCSIG__
#else
    #define BE_FUNC_SIG __PRETTY_FUNCTION__
#endif

[[noreturn]] inline void VERIFY_NOT_REACHED() {
    assert(false || "Unreachable");
    abort();
}

#ifdef DEBUG
    #define BE_GL_DEBUG 1
#endif

}  // namespace BillyEngine