#pragma once

// Taken from https://gcc.gnu.org/wiki/Visibility but adapted by me

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define BE_PUBLIC __attribute__((dllexport))
    #else
    // Note: actually gcc seems to also supports this syntax.
        #define BE_PUBLIC __declspec(dllexport)
    #endif
    #define BE_LOCAL
#else
    #define BE_PUBLIC __attribute__((visibility("default")))
    #define BE_LOCAL __attribute__((visibility("hidden")))
#endif

#ifdef __cplusplus
    #define BE_HEADER_START extern "C" {
    #define BE_HEADER_END }
#else
    #define BE_HEADER_START
    #define BE_HEADER_END
#endif