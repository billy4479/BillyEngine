if(SYSTEM_DEPENDENCIES)
    find_package(spdlog)
else()
    set(SPDLOG_NO_EXCEPTIONS ON)
    set(SPDLOG_FMT_EXTERNAL ON)
    message(STATUS "Getting spdlog ready...")
    FetchContent_Declare(spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog"
        GIT_TAG "v1.9.2"
    )
    FetchContent_MakeAvailable(spdlog)
endif()