if(SYSTEM_DEPENDENCIES)
    find_package(EnTT)
else()
    message(STATUS "Getting EnTT ready...")
    FetchContent_Declare(EnTT
        GIT_REPOSITORY "https://github.com/skypjack/entt"
        GIT_TAG "v3.8.1"
    )
    FetchContent_MakeAvailable(EnTT)
endif()