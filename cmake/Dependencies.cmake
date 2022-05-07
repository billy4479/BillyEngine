if(BUILD_SHARED_LIBS AND BUNDLE_DEPENDENCIES AND NOT SYSTEM_DEPENDENCIES)
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUNDLE_DEPENDENCIES OFF)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies)

include(FetchContent)

include(entt)
include(fmt)
include(GLAD)
include(GLFW)
include(glm)
include(spdlog)
include(stb_image)

if(BUNDLE_DEPENDENCIES)
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/WHOLEARCHIVE"
        )
    elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-Wl,-all_load"
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-Wl,--whole-archive"
        )
    endif()
endif()

target_link_libraries(
    ${PROJECT_NAME}_objs
    PUBLIC glm
    PRIVATE EnTT::EnTT glad glfw spdlog::spdlog stb_image fmt
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC glm
    PRIVATE EnTT::EnTT glad glfw spdlog::spdlog stb_image fmt
)

if(GENERATE_BINDINGS)
    swig_link_libraries(
        ${PROJECT_NAME}_swig
        PUBLIC glm
        PRIVATE EnTT::EnTT glad glfw spdlog::spdlog stb_image fmt
    )
endif()

if(BUNDLE_DEPENDENCIES)
    if(MSVC)
        # TODO: is there a option for MSVC too?
    elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-Wl,-noall_load"
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-Wl,--no-whole-archive"
        )
    endif()
endif()
