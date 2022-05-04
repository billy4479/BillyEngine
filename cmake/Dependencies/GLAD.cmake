# GLAD has to be downloaded/generated

message(STATUS "Getting GLAD ready...")
FetchContent_Declare(
  glad
  GIT_REPOSITORY "https://github.com/Dav1dde/glad"
  GIT_TAG "glad2"
)

FetchContent_GetProperties(glad)

if(NOT glad_POPULATED)
  FetchContent_Populate(glad)

  add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
  glad_add_library(glad API gl:core=4.6)
endif()