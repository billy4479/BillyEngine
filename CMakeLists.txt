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

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

message(STATUS "Getting EnTT ready...")
FetchContent_Declare(EnTT
    GIT_REPOSITORY "https://github.com/skypjack/entt"
    GIT_TAG "v3.8.1"
)
FetchContent_MakeAvailable(EnTT)

message(STATUS "Getting glm ready...")
FetchContent_Declare(glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG "0.9.9.8"
)
FetchContent_MakeAvailable(glm)


aux_source_directory( src SOURCES)
aux_source_directory( src/Core CORE)
aux_source_directory( src/Entity ENTITY)
aux_source_directory( src/Rendering RENDERING)

add_library( ${PROJECT_NAME} SHARED ${SOURCES} ${CORE} ${RENDERING} ${ENTITY})

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL2::Main SDL2::TTF SDL2::Image EnTT glm
)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/Core/Common.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/include)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()

