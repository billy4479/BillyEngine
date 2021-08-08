cmake_minimum_required(VERSION 3.10)

project(sdl-tests LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2-cmake-modules)

option(CROSS_COMPILE_WINDOWS "Cross compile for windows" OFF)
# option(STATIC "Build a static executable" OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

aux_source_directory( src SOURCES)
aux_source_directory( src/Core CORE)
aux_source_directory( src/Entity ENTITY)
aux_source_directory( src/Rendering RENDERING)

add_executable( ${PROJECT_NAME} ${SOURCES} ${CORE} ${ENTITY} ${RENDERING})

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

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::TTF SDL2::Image )

target_precompile_headers(${PROJECT_NAME} PRIVATE src/Core/Common.hpp)

file(GLOB ASSETS "assets/*")
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
