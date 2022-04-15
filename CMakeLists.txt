cmake_minimum_required(VERSION 3.18)

project(BillyEngine LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

option(COMPILE_DEMO "Compile the demo program" ON)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Found ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

message(STATUS "Getting GLAD ready...")
FetchContent_Declare(glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "glad2"
)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  FetchContent_Populate(glad)

  add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
  glad_add_library(glad API gl:core=4.6)
endif()
# FetchContent_MakeAvailable(glad)

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

set(SPDLOG_NO_EXCEPTIONS ON)
message(STATUS "Getting spdlog ready...")
FetchContent_Declare(spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog"
    GIT_TAG "v1.9.2"
)
FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp include/*.h include/*.hpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/WHOLEARCHIVE"
    )
elseif (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-Wl,-all_load"
    )
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-Wl,--whole-archive"
    )
endif ()


target_link_libraries(${PROJECT_NAME}
    PRIVATE glad glfw EnTT glm spdlog::spdlog
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC include
    PRIVATE src
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -pedantic -Werror -fno-exceptions -fno-rtti>
)

if (WIN32)
elseif (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-Wl,-noall_load"
    )
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-Wl,--no-whole-archive"
    )
endif ()

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()

