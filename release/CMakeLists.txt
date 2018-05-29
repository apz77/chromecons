configure_file(
    "src/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
)

set(BOOST_DIR vendors/boost)

add_executable(chromecons src/main.cpp)

include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(include)
include_directories(${BOOST_DIR})
include_directories(vendors/sqlite)
include_directories(vendors/http-parser)

add_subdirectory(vendors)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c" "include/*.h")

if (WIN32)
    file(GLOB BOOST_LIBS "${BOOST_DIR}/stage/lib/*.lib")
else()
    file(GLOB BOOST_LIBS "${BOOST_DIR}/lib/*.a")
endif()

message("${BOOST_LIBS}")

link_directories(${BOOST_DIR}/stage/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
set_target_properties(http-parser PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

target_link_libraries(chromecons sqlite3 http-parser ${BOOST_LIBS})

if (UNIX)
    target_link_libraries(chromecons pthread dl)
else()
    target_link_libraries(chromecons Shell32.lib)
endif()

target_sources(chromecons PUBLIC ${SOURCE_FILES})

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
endif()
