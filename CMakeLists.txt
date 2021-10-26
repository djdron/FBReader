cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(FBReader)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

add_subdirectory("zlibrary/core" "zlcore")
