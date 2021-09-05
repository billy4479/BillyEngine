#pragma once

#include "PlatformDetection.hpp"

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

    #define BE_ASSERT(test)                                      \
        if (test) {                                              \
            dbg_print("Assertion failed in " __FILE__            \
                      " at line %d in function %s: " #test "\n", \
                      __LINE__, __FUNCTION__);                   \
            fflush(stdout);                                      \
            BE_TRAP;                                             \
        }

#else
    #define BE_ASSERT(...)
#endif
