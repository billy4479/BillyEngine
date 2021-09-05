#pragma once

#include "PlatformDetection.hpp"

#ifndef NDEBUG
    #define DEBUG 1
#endif

#define BE_USE_CUSTOM_ASSERT 1
#ifdef DEBUG
    #if defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
        #define BE_TRAP __builtin_debugtrap();
    #elif defined _WIN32
        #define BE_TRAP __debugbreak();
    #else
        #include <signal.h>
        #ifndef SIGTRAP
            #error "Compiler has no trap"
        #endif
        #define BE_TRAP raise(SIGTRAP);
    #endif

    #if BE_USE_CUSTOM_ASSERT
        #define BE_ASSERT(check)                                  \
            {                                                     \
                if (!(check)) {                                   \
                    dbg_print("Assertion failed in " __FILE__     \
                              ":%d in function %s: " #check "\n", \
                              __LINE__, __FUNCTION__);            \
                    fflush(stderr);                               \
                    BE_TRAP;                                      \
                }                                                 \
            }
    // #else
    //     #include <cassert>
    //     #define BE_ASSERT(...) assert(__VA_ARGS__);
    #endif

#else
    #define BE_ASSERT(...)
    #define BE_TRAP
#endif
