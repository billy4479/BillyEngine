cmake_minimum_required(VERSION 3.14)

project(BillyEngine LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2-cmake-modules)
include(FetchContent)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

option(COMPILE_DEMO "Compile the demo program" ON)
option(CROSS_COMPILE_WINDOWS "Cross compile for windows" OFF)
# option(STATIC "Build a static executable" OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

message(STATUS "Downloading EnTT...")
FetchContent_Declare(EnTT
    GIT_REPOSITORY "https://github.com/skypjack/entt"
    GIT_TAG "0754f108c99ed2adce12b8d1bdf370169d103614"
)
FetchContent_MakeAvailable(EnTT)

aux_source_directory( src SOURCES)
aux_source_directory( src/Core CORE)
aux_source_directory( src/Rendering RENDERING)

add_library( ${PROJECT_NAME} SHARED ${SOURCES} ${CORE} ${RENDERING})

if(STATIC)
target_link_libraries(${PROJECT_NAME} PRIVATE -static)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

if(CROSS_COMPILE_WINDOWS)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::Main SDL2::TTF SDL2::Image EnTT )

target_precompile_headers(${PROJECT_NAME} PRIVATE src/Core/Common.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/include)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()

