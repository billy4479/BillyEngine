#pragma once

#include <BillyEngine/Utils.h>

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

#define BE_NON_COPYABLE(className)        \
    className(const className&) = delete; \
    className& operator=(const className&) = delete;

#define BE_NON_MOVABLE(className)    \
    className(className&&) = delete; \
    className& operator=(className&&) = delete;

#define BE_NON_COPYABLE_NON_MOVABLE(className) \
    BE_NON_COPYABLE(className)                 \
    BE_NON_MOVABLE(className)

#define BE_DEFAULT_COPY(className)         \
    className(const className&) = default; \
    className& operator=(const className&) = default;

#define BE_DEFAULT_MOVE(className)    \
    className(className&&) = default; \
    className& operator=(className&&) = default;

#define BE_DEFAULT_COPY_AND_MOVE(className) \
    BE_DEFAULT_COPY(className)              \
    BE_DEFAULT_MOVE(className)

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

#define BE_GL_LOG 1

#if defined(DEBUG) && BE_GL_LOG
    #define BE_GL_DEBUG 0  // Enable logging of every GL call
#else
    #define BE_GL_DEBUG 0
#endif

}  // namespace BillyEngine