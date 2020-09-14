cmake_minimum_required (VERSION 3.12)
project (OpenWx)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_POSITION_INDEPENDENT_CODE 1)
set (XPLANE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDK CACHE PATH "X-Plane SDK")

if (NOT EXISTS ${XPLANE_SDK_PATH})
    message (FATAL_ERROR "X-Plane SDK path incorrect")
endif ()

add_subdirectory (3rdparty)
add_subdirectory (src)
