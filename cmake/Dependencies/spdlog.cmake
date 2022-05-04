set(SPDLOG_NO_EXCEPTIONS ON)
set(SPDLOG_FMT_EXTERNAL ON)

if(SYSTEM_DEPENDENCIES)
    find_package(spdlog)
else()
    message(STATUS "Getting spdlog ready...")
    FetchContent_Declare(spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog"
        GIT_TAG "v1.9.2"
    )
    FetchContent_MakeAvailable(spdlog)
endif()

target_compile_definitions(spdlog::spdlog INTERFACE SPDLOG_NO_EXCEPTIONS)
target_compile_definitions(spdlog::spdlog INTERFACE SPDLOG_FMT_EXTERNAL)