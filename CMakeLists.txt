cmake_minimum_required (VERSION 2.6)
project (chromecons)

set(PROJECT_VERSION 1.1)
set(PROJECT_DESCRIPTION BastionPass Chrome extraction utility)

add_subdirectory(release)

IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Debug)
ENDIF()
