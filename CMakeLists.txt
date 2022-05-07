cmake_minimum_required(VERSION 3.18)

project(BillyEngine LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(COMPILE_DEMO "Compile the demo program" ON)
option(BUILD_SHARED_LIBS "Build a shaded library" ON)
option(BUNDLE_DEPENDENCIES "Bundle all the dependencies in the same dll" ON)
option(SYSTEM_DEPENDENCIES "Use system dependencies instead of downloading and building them" OFF)
option(GENERATE_BINDINGS "Generate bindings using swig" ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CompilerFlags)
include(GeneratorSetup)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp include/*.h include/*.hpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(
        ${PROJECT_NAME}_objs
        OBJECT
        ${SRC} ${BE_GENERATED_FILES}
)
set_compiler_flags(${PROJECT_NAME}_objs)

add_library(${PROJECT_NAME} $<TARGET_OBJECTS:${PROJECT_NAME}_objs>)
set_compiler_flags(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}_objs 
    PRIVATE include include/BillyEngine ${PROJECT_BINARY_DIR}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)

include(SWIG)
include(Dependencies)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()
