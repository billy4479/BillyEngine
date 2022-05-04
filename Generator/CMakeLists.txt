cmake_minimum_required(VERSION 3.18)

# project(Generator LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE GENERATOR_SRC src/*.cpp src/*.hpp)

add_executable(Generator ${GENERATOR_SRC})

set_compiler_flags(Generator)

target_link_libraries(Generator PRIVATE stb_image fmt)

export(TARGETS Generator FILE "${CMAKE_BINARY_DIR}/GenConfig.cmake")
