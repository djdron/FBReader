cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(FBReader)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0 -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4267 /wd4244")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

add_subdirectory("third-party/zlib" "zlib")
set_property(TARGET zlib PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET zlibstatic PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET example PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET minigzip PROPERTY FOLDER "3rdparty/zlib")

get_target_property(ZLIB_BINARY_DIR zlib BINARY_DIR)
get_target_property(ZLIB_SOURCE_DIR zlib SOURCE_DIR)
include_directories(${ZLIB_BINARY_DIR} ${ZLIB_SOURCE_DIR})

set(BZIP2_SRCS
    "third-party/bzip2/blocksort.c"
    "third-party/bzip2/huffman.c"
    "third-party/bzip2/crctable.c"
    "third-party/bzip2/randtable.c"
    "third-party/bzip2/compress.c"
    "third-party/bzip2/decompress.c"
    "third-party/bzip2/bzlib.c"
)
add_library(bzip2 SHARED ${BZIP2_SRCS})
include_directories("third-party/bzip2")
set_property(TARGET bzip2 PROPERTY FOLDER "3rdparty")

set(EXPAT_BUILD_EXAMPLES OFF)
set(EXPAT_BUILD_TESTS OFF)
set(EXPAT_BUILD_TOOLS OFF)
add_subdirectory("third-party/libexpat/expat" "libexpat")
set_property(TARGET expat PROPERTY FOLDER "3rdparty")

get_target_property(EXPAT_SOURCE_DIR expat SOURCE_DIR)
include_directories("${EXPAT_SOURCE_DIR}/lib")


add_definitions(-DBASEDIR="/share")
add_definitions(-DIMAGEDIR="/share/icons")
add_definitions(-DAPPIMAGEDIR="/share/icons")

add_subdirectory("zlibrary/core" "zlcore")
