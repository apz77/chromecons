configure_file(
    "src/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
)

add_executable(chromecons src/main.cpp)

include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(include)

add_subdirectory(vendors)

file(GLOB SOURCE_FILES "src/*.cpp" "src/*.c")

set(SOURCES
    ${SOURCE_FILES}
)