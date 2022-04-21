cmake_minimum_required(VERSION 3.18)

# project(Generator LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE GENERATOR_SRC *.cpp *.hpp)

add_executable(Generator ${GENERATOR_SRC})

target_compile_options(Generator PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -pedantic -Werror -fno-exceptions -fno-rtti>
)

target_link_libraries(Generator PRIVATE stb_image)
