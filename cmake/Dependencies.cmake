if(BUILD_SHARED_LIBS)
    if(BUNLD_DEPENDENCIES AND NOT SYSTEM_DEPENDENCIES)
        set(BUILD_SHARED_LIBS OFF)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    else()
        set(BUILD_SHARED_LIBS ON)
    endif()
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

if(BUNLD_DEPENDENCIES)
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

target_link_libraries(${PROJECT_NAME}
    PUBLIC glm fmt
    PRIVATE EnTT::EnTT glad glfw spdlog::spdlog stb_image
)

if(BUNLD_DEPENDENCIES)
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
