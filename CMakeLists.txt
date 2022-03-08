cmake_minimum_required(VERSION 3.18)

project(BillyEngine LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

option(COMPILE_DEMO "Compile the demo program" ON)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Found ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

message(STATUS "Getting GLAD ready...")
FetchContent_Declare(GLAD
    GIT_REPOSITORY "https://github.com/billy4479/glad-cmake"
    GIT_TAG "master"
)
FetchContent_MakeAvailable(GLAD)

message(STATUS "Getting GLFW ready...")
FetchContent_Declare(glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw"
    GIT_TAG "3.3.6"
)
FetchContent_MakeAvailable(glfw)

message(STATUS "Getting glm ready...")
FetchContent_Declare(glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG "0.9.9.8"
)
FetchContent_MakeAvailable(glm)

message(STATUS "Getting EnTT ready...")
FetchContent_Declare(EnTT
    GIT_REPOSITORY "https://github.com/skypjack/entt"
    GIT_TAG "v3.8.1"
)
FetchContent_MakeAvailable(EnTT)

message(STATUS "Getting spdlog ready...")
FetchContent_Declare(spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog"
    GIT_TAG "v1.9.2"
)
FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC GLAD glfw EnTT glm spdlog::spdlog
)

target_include_directories(${PROJECT_NAME} PUBLIC src/include)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -pedantic -Werror -fno-exceptions -fno-rtti>
)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()

