#pragma once

#include "../Core/PlatformDetection.hpp"

#ifdef DEBUG
    #if defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
        #define BE_TRAP() __builtin_debugtrap()
    #elif defined _WIN32
        #define BE_TRAP() __debugbreak()
    #else
        #include <signal.h>
        #ifndef SIGTRAP
            #error "Compiler has no trap"
        #endif
        #define BE_TRAP() raise(SIGTRAP)
    #endif

    #if BE_USE_CUSTOM_ASSERT
        #define BE_ASSERT(check)                                        \
            {                                                           \
                if (!(check)) {                                         \
                    BE_CORE_CRITICAL(                                   \
                        "Assertion failed in {}:{} in function {}: {}", \
                        __FILE__, __LINE__, __FUNCTION__, #check);      \
                    BE_TRAP();                                          \
                }                                                       \
            }
    #else
        #include <cassert>
        #define BE_ASSERT(...) assert(__VA_ARGS__)
    #endif

    #define BE_ABORT() BE_TRAP()

    #define BE_CHECK_SDL_ERROR_AND_DIE()                         \
        {                                                        \
            auto err = SDL_GetError();                           \
            if (err != nullptr && strlen(err) != 0) {            \
                BE_CORE_CRITICAL("SDL error occurred: {}", err); \
                BE_TRAP();                                       \
            }                                                    \
        }

#else
    #define BE_ASSERT(...)
    #define BE_TRAP()
    #define BE_ABORT() abort()
    #define BE_CHECK_SDL_ERROR_AND_DIE()
#endif
