#pragma once

// Taken from https://gcc.gnu.org/wiki/Visibility but adapted by me

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        // #define BE_API_IMPL __attribute__((dllimport))
        #define BE_API __attribute__((dllexport))
    #else
        // #define BE_API_IMPL __declspec(dllimport)
        #define BE_API __declspec(dllexport)
    #endif
#else
    #define BE_API __attribute__((visibility("default")))
// #define BE_API_IMPL __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
    #define BE_HEADER_START extern "C" {
    #define BE_HEADER_END }
#else
    #define BE_HEADER_START
    #define BE_HEADER_END
#endif