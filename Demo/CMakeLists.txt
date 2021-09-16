cmake_minimum_required(VERSION 3.14)

project(Demo LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp TestEntity.cpp TestEntity2.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE BillyEngine)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -pedantic -Werror>
)

file(GLOB ASSETS "assets/*")
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
