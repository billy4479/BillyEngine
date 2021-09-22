cmake_minimum_required(VERSION 3.14)

project(BillyEngine LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2-cmake-modules)
include(FetchContent)

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

message(STATUS "Getting spdlog ready...")
FetchContent_Declare(spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog"
    GIT_TAG "v1.9.2"
)
FetchContent_MakeAvailable(spdlog)

aux_source_directory( src SOURCES)
aux_source_directory( src/Core CORE)
aux_source_directory( src/Components COMPONENTS)
aux_source_directory( src/Entity ENTITY)
aux_source_directory( src/Event EVENT)
aux_source_directory( src/Rendering RENDERING)
aux_source_directory( src/Window WINDOW)
aux_source_directory( src/Wrappers WRAPPERS)

list(APPEND SOURCES ${COMPONENTS} ${CORE} ${RENDERING} ${ENTITY} ${EVENT} ${WINDOW} ${WRAPPERS})

# Maybe just in debug mode?
aux_source_directory( src/Debugging DEBUGGING)
list(APPEND SOURCES ${DEBUGGING})

add_library( ${PROJECT_NAME} STATIC ${SOURCES} )

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL2::Main SDL2::TTF SDL2::Image EnTT glm spdlog::spdlog
)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/Core/STDInclude.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/include)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -pedantic -Werror>
)

if(COMPILE_DEMO)
    add_subdirectory(Demo)
endif()

