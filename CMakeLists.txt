cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(FBReader)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0 -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4267 /wd4244")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif()

add_definitions(-DUNICODE -D_UNICODE)

include_directories("third-party/zlib")

add_subdirectory("third-party/zlib" "zlib")
set_property(TARGET zlib PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET zlibstatic PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET example PROPERTY FOLDER "3rdparty/zlib")
set_property(TARGET minigzip PROPERTY FOLDER "3rdparty/zlib")

get_target_property(ZLIB_BINARY_DIR zlib BINARY_DIR)
get_target_property(ZLIB_SOURCE_DIR zlib SOURCE_DIR)
include_directories(${ZLIB_BINARY_DIR} ${ZLIB_SOURCE_DIR})

set(CMAKE_DEBUG_POSTFIX "")

set(BZIP2_SRCS
    "third-party/bzip2/blocksort.c"
    "third-party/bzip2/huffman.c"
    "third-party/bzip2/crctable.c"
    "third-party/bzip2/randtable.c"
    "third-party/bzip2/compress.c"
    "third-party/bzip2/decompress.c"
    "third-party/bzip2/bzlib.c"
)
add_library(bzip2 STATIC ${BZIP2_SRCS})
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

add_definitions(-DDONT_HAVE_FRIBIDI_CONFIG_H -DHAVE_STRINGIZE -DFRIBIDI_LIB_STATIC -DHAVE_STDLIB_H -DHAVE_STRING_H)
add_executable(gen-unicode-version "third-party/fribidi/gen.tab/gen-unicode-version.c")
set_property(TARGET gen-unicode-version PROPERTY FOLDER "3rdparty/fribidi/gen.tab")

set(FGENWD "${CMAKE_CURRENT_SOURCE_DIR}/third-party/fribidi/gen.tab")
set(FUV "${CMAKE_CURRENT_BINARY_DIR}/fribidi-unicode-version.h")
add_custom_command(OUTPUT ${FUV}
	COMMAND gen-unicode-version "unidata/ReadMe.txt" "unidata/BidiMirroring.txt" > ${FUV}
	WORKING_DIRECTORY ${FGENWD}
)

add_custom_target(fribidi-unicode-version
	DEPENDS ${FUV}
)
set_property(TARGET fribidi-unicode-version PROPERTY FOLDER "3rdparty/fribidi/gen.tab")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PACKTAB "third-party/fribidi/gen.tab/packtab.c")

add_executable(gen-bidi-type-tab "third-party/fribidi/gen.tab/gen-bidi-type-tab.c" ${PACKTAB})
add_executable(gen-joining-type-tab "third-party/fribidi/gen.tab/gen-joining-type-tab.c" ${PACKTAB})
add_executable(gen-arabic-shaping-tab "third-party/fribidi/gen.tab/gen-arabic-shaping-tab.c" ${PACKTAB})
add_executable(gen-mirroring-tab "third-party/fribidi/gen.tab/gen-mirroring-tab.c" ${PACKTAB})
add_executable(gen-brackets-tab "third-party/fribidi/gen.tab/gen-brackets-tab.c" ${PACKTAB})
add_executable(gen-brackets-type-tab "third-party/fribidi/gen.tab/gen-brackets-type-tab.c" ${PACKTAB})

add_dependencies(gen-bidi-type-tab fribidi-unicode-version)
add_dependencies(gen-joining-type-tab fribidi-unicode-version)
add_dependencies(gen-arabic-shaping-tab fribidi-unicode-version)
add_dependencies(gen-mirroring-tab fribidi-unicode-version)
add_dependencies(gen-brackets-tab fribidi-unicode-version)
add_dependencies(gen-brackets-type-tab fribidi-unicode-version)

set_property(TARGET gen-bidi-type-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")
set_property(TARGET gen-joining-type-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")
set_property(TARGET gen-arabic-shaping-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")
set_property(TARGET gen-mirroring-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")
set_property(TARGET gen-brackets-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")
set_property(TARGET gen-brackets-type-tab PROPERTY FOLDER "3rdparty/fribidi/gen.tab")

set(BIDIDEPTH 2)
set(BIDITYPETABI "${CMAKE_CURRENT_BINARY_DIR}/bidi-type.tab.i")
add_custom_command(OUTPUT ${BIDITYPETABI}
	COMMAND gen-bidi-type-tab ${BIDIDEPTH} "unidata/UnicodeData.txt" > ${BIDITYPETABI}
	WORKING_DIRECTORY ${FGENWD}
)
set(JOININGTYPETABI "${CMAKE_CURRENT_BINARY_DIR}/joining-type.tab.i")
add_custom_command(OUTPUT ${JOININGTYPETABI}
	COMMAND gen-joining-type-tab ${BIDIDEPTH} "unidata/UnicodeData.txt" "unidata/ArabicShaping.txt" > ${JOININGTYPETABI}
	WORKING_DIRECTORY ${FGENWD}
)
set(ARABICSHAPINGTABI "${CMAKE_CURRENT_BINARY_DIR}/arabic-shaping.tab.i")
add_custom_command(OUTPUT ${ARABICSHAPINGTABI}
	COMMAND gen-arabic-shaping-tab ${BIDIDEPTH} "unidata/UnicodeData.txt" > ${ARABICSHAPINGTABI}
	WORKING_DIRECTORY ${FGENWD}
)
set(MIRRORINGTABI "${CMAKE_CURRENT_BINARY_DIR}/mirroring.tab.i")
add_custom_command(OUTPUT ${MIRRORINGTABI}
	COMMAND gen-mirroring-tab ${BIDIDEPTH} "unidata/BidiMirroring.txt" > ${MIRRORINGTABI}
	WORKING_DIRECTORY ${FGENWD}
)
set(BRACKETSTABI "${CMAKE_CURRENT_BINARY_DIR}/brackets.tab.i")
add_custom_command(OUTPUT ${BRACKETSTABI}
	COMMAND gen-brackets-tab ${BIDIDEPTH} "unidata/BidiBrackets.txt" "unidata/UnicodeData.txt" > ${BRACKETSTABI}
	WORKING_DIRECTORY ${FGENWD}
)
set(BRACKETSTYPETABI "${CMAKE_CURRENT_BINARY_DIR}/brackets-type.tab.i")
add_custom_command(OUTPUT ${BRACKETSTYPETABI}
	COMMAND gen-brackets-type-tab ${BIDIDEPTH} "unidata/BidiBrackets.txt" > ${BRACKETSTYPETABI}
	WORKING_DIRECTORY ${FGENWD}
)


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
	${BIDITYPETABI}
	${JOININGTYPETABI}
	${ARABICSHAPINGTABI}
	${MIRRORINGTABI}
	${BRACKETSTABI}
	${BRACKETSTYPETABI}
)
add_library(fribidi STATIC ${FRIBIDI_SRCS})
include_directories("third-party/fribidi/lib")
set_property(TARGET fribidi PROPERTY FOLDER "3rdparty/fribidi")


add_definitions(-DBASEDIR="/share")
add_definitions(-DIMAGEDIR="/share/icons")
add_definitions(-DAPPIMAGEDIR="/share/icons")

add_subdirectory("zlibrary/core" "zlcore")
get_target_property(ZLCORE_SOURCE_DIR zlcore SOURCE_DIR)
include_directories("${ZLCORE_SOURCE_DIR}/include")
target_link_libraries(zlcore zlib bzip2 expat libunibreak)

add_subdirectory("zlibrary/text" "zltext")
get_target_property(ZLTEXT_SOURCE_DIR zltext SOURCE_DIR)
include_directories("${ZLTEXT_SOURCE_DIR}/include")
target_link_libraries(zltext zlcore fribidi)

add_subdirectory("zlibrary/ui" "zlui")

add_subdirectory("third-party/sqlite" "sqlite")
set_property(TARGET SQLite3 PROPERTY FOLDER "3rdparty")
get_target_property(SQLITE_SOURCE_DIR SQLite3 SOURCE_DIR)
include_directories("${SQLITE_SOURCE_DIR}")

add_subdirectory("fbreader")
target_link_libraries(fbreader zlcore zltext zlui SQLite3)
