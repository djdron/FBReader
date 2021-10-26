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

add_definitions(-DUNICODE -D_UNICODE)

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

set(UNIBREAK_SRCS
	"third-party/libunibreak/src/unibreakbase.c"
	"third-party/libunibreak/src/unibreakdef.c"
	"third-party/libunibreak/src/linebreak.c"
	"third-party/libunibreak/src/linebreakdata.c"
	"third-party/libunibreak/src/linebreakdef.c"
	"third-party/libunibreak/src/emojidef.c"
	"third-party/libunibreak/src/graphemebreak.c"
	"third-party/libunibreak/src/wordbreak.c"
)
add_library(libunibreak STATIC ${UNIBREAK_SRCS})
include_directories("third-party/libunibreak/src")
set_property(TARGET libunibreak PROPERTY FOLDER "3rdparty")

set(FRIBIDI_SRCS
	"third-party/fribidi/lib/fribidi.c"
	"third-party/fribidi/lib/fribidi-arabic.c"
	"third-party/fribidi/lib/fribidi-bidi.c"
	"third-party/fribidi/lib/fribidi-bidi-types.c"
	"third-party/fribidi/lib/fribidi-char-sets.c"
	"third-party/fribidi/lib/fribidi-char-sets-cap-rtl.c"
	"third-party/fribidi/lib/fribidi-char-sets-cp1255.c"
	"third-party/fribidi/lib/fribidi-char-sets-cp1256.c"
	"third-party/fribidi/lib/fribidi-char-sets-iso8859-6.c"
	"third-party/fribidi/lib/fribidi-char-sets-iso8859-8.c"
	"third-party/fribidi/lib/fribidi-char-sets-utf8.c"
	"third-party/fribidi/lib/fribidi-deprecated.c"
	"third-party/fribidi/lib/fribidi-joining.c"
	"third-party/fribidi/lib/fribidi-joining-types.c"
	"third-party/fribidi/lib/fribidi-mirroring.c"
	"third-party/fribidi/lib/fribidi-brackets.c"
	"third-party/fribidi/lib/fribidi-run.c"
	"third-party/fribidi/lib/fribidi-shape.c"
)
add_definitions(-DDONT_HAVE_FRIBIDI_CONFIG_H -DHAVE_STRINGIZE -DFRIBIDI_LIB_STATIC -DHAVE_STDLIB_H)
add_library(fribidi STATIC ${FRIBIDI_SRCS})
include_directories("third-party/fribidi/lib")
set_property(TARGET fribidi PROPERTY FOLDER "3rdparty")


add_definitions(-DBASEDIR="/share")
add_definitions(-DIMAGEDIR="/share/icons")
add_definitions(-DAPPIMAGEDIR="/share/icons")

add_subdirectory("zlibrary/core" "zlcore")
get_target_property(ZLCORE_SOURCE_DIR zlcore SOURCE_DIR)
include_directories("${ZLCORE_SOURCE_DIR}/include")
add_subdirectory("zlibrary/text" "zltext")
