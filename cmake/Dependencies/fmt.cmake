if(SYSTEM_DEPENDENCIES)
    find_package(fmt)
else()
    message(STATUS "Getting fmt ready...")
    FetchContent_Declare(fmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt"
    GIT_TAG "8.1.1"
    )
    FetchContent_MakeAvailable(fmt)
endif()