cmake_minimum_required(VERSION 3.14)

project(Demo LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE BillyEngine)

file(GLOB ASSETS "assets/*")
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
