#pragma once

// Taken from https://gcc.gnu.org/wiki/Visibility but adapted by me

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define BE_PUBLIC extern __attribute__((dllexport))
    #else
    // Note: actually gcc seems to also supports this syntax.
        #define BE_PUBLIC extern __declspec(dllexport)
    #endif
#else
    #define BE_PUBLIC extern __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
    #define BE_HEADER_START extern "C" {
    #define BE_HEADER_END }
#else
    #define BE_HEADER_START
    #define BE_HEADER_END
#endif