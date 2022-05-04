cmake_minimum_required(VERSION 3.18)

project(BillyEngine LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(COMPILE_DEMO "Compile the demo program" ON)
option(BUILD_SHARED_LIBS "Build a shaded library" ON)
option(BUNDLE_DEPENDENCIES "Bundle all the dependencies in the same dll" ON)
option(SYSTEM_DEPENDENCIES "Use system dependencies instead of downloading and building them" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CompilerFlags)
include(GeneratorSetup)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp include/*.h include/*.hpp)
add_library(${PROJECT_NAME} ${SRC} ${BE_GENERATED_FILES})

set_compiler_flags(${PROJECT_NAME})
include(Dependencies)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} 
    PUBLIC include src
    PRIVATE include/BillyEngine++
)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()
