# This also have to be downloaded

message(STATUS "Getting stb_image ready...")
FetchContent_Declare(stb_image
    GIT_REPOSITORY "https://github.com/billy4479/stb_image-cmake"
    GIT_TAG "master"
)
FetchContent_MakeAvailable(stb_image)