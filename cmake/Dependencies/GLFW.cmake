if (SYSTEM_DEPENDENCIES)
    find_package(glfw3)
else()
    message(STATUS "Getting GLFW ready...")
    FetchContent_Declare(glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw"
        GIT_TAG "3.3.6"
    )
    FetchContent_MakeAvailable(glfw)
endif()
