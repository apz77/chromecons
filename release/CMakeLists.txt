configure_file(
    "src/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
)

if (STAGE)
    add_definitions(-DDEV=true)
endif()

set(BOOST_DIR libs/boost)

if(MSVC)
  set(BUILD_SHARED_LIBS false)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /MT")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /Zi /MT") 
  add_definitions(-D_WIN32_WINNT=0x0501)
  # Force static runtime libraries
  FOREACH(flag
   CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
   CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
   CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
   CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
   STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
   SET("${flag}" "${${flag}} /EHsc")
  ENDFOREACH()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
endif()

add_executable(chromecons src/main.cpp)

include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(include)
include_directories(${BOOST_DIR}/include)
include_directories(vendors/sqlite)
include_directories(vendors/http-parser)

add_subdirectory(vendors)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c" "include/*.h")

if (WIN32)
    file(GLOB BOOST_LIBS "${BOOST_DIR}/stage/lib/*.lib")
    link_directories(${BOOST_DIR}/stage/lib)    
else()
    file(GLOB BOOST_LIBS "${BOOST_DIR}/lib/*.a")
    link_directories(${BOOST_DIR}/lib)
endif()

message("${BOOST_LIBS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
set_target_properties(http-parser PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

target_link_libraries(chromecons sqlite3 http-parser ${BOOST_LIBS})

if (UNIX)
    target_link_libraries(chromecons pthread dl -static-libgcc -static-libstdc++)
else()
    target_link_libraries(chromecons Shell32.lib)
endif()

target_sources(chromecons PUBLIC ${SOURCE_FILES})
