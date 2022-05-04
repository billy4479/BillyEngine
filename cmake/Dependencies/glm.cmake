if(SYSTEM_DEPENDENCIES)
    find_package(glm)
else()
    message(STATUS "Getting glm ready...")
    FetchContent_Declare(glm
        GIT_REPOSITORY "https://github.com/g-truc/glm"
        GIT_TAG "master"
    )
    FetchContent_MakeAvailable(glm)
endif()