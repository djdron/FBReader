cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(FBReader)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4267 /wd4244")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif()

add_definitions(-DUNICODE -D_UNICODE)

include_directories("third-party/zlib")

add_subdirectory("third-party/zlib" "zlib" EXCLUDE_FROM_ALL)
set_property(TARGET zlib PROPERTY FOLDER "3rdparty")

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
add_subdirectory("third-party/libexpat/expat" "libexpat" EXCLUDE_FROM_ALL)
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


add_definitions(-DBASEDIR=".")
add_definitions(-DIMAGEDIR="./icons")
add_definitions(-DAPPIMAGEDIR="./icons")

add_subdirectory("zlibrary/core" "zlcore")
get_target_property(ZLCORE_SOURCE_DIR zlcore SOURCE_DIR)
include_directories("${ZLCORE_SOURCE_DIR}/include")
target_link_libraries(zlcore zlib bzip2 expat libunibreak)

add_subdirectory("zlibrary/text" "zltext")
get_target_property(ZLTEXT_SOURCE_DIR zltext SOURCE_DIR)
include_directories("${ZLTEXT_SOURCE_DIR}/include")
target_link_libraries(zltext zlcore fribidi)

add_subdirectory("zlibrary/ui" "zlui")

add_subdirectory("third-party/sqlite" "sqlite" EXCLUDE_FROM_ALL)
set_property(TARGET SQLite3 PROPERTY FOLDER "3rdparty")
get_target_property(SQLITE_SOURCE_DIR SQLite3 SOURCE_DIR)
include_directories("${SQLITE_SOURCE_DIR}")

add_subdirectory("fbreader")
target_link_libraries(fbreader zlcore zltext zlui SQLite3)

set(QT_PATH "${CMAKE_PREFIX_PATH}/../..")
set(QT_LIBRARIES_INSTALL
	"${QT_PATH}/bin/Qt5Core.dll"
	"${QT_PATH}/bin/Qt5Gui.dll"
	"${QT_PATH}/bin/Qt5Network.dll"
	"${QT_PATH}/bin/Qt5Svg.dll"
	"${QT_PATH}/bin/Qt5Widgets.dll"
)
set(QT_IMAGEFORMATS_INSTALL
	"${QT_PATH}/plugins/imageformats/qgif.dll"
	"${QT_PATH}/plugins/imageformats/qicns.dll"
	"${QT_PATH}/plugins/imageformats/qico.dll"
	"${QT_PATH}/plugins/imageformats/qjpeg.dll"
	"${QT_PATH}/plugins/imageformats/qsvg.dll"
	"${QT_PATH}/plugins/imageformats/qtga.dll"
	"${QT_PATH}/plugins/imageformats/qtiff.dll"
	"${QT_PATH}/plugins/imageformats/qwbmp.dll"
	"${QT_PATH}/plugins/imageformats/qwebp.dll"
)

if(WIN32)
set(CPACK_PACKAGE_EXECUTABLES fbreader "FBReader")
install(TARGETS fbreader zlib expat RUNTIME DESTINATION ".")
install(FILES		 ${QT_LIBRARIES_INSTALL} DESTINATION ".")
install(FILES		 ${QT_IMAGEFORMATS_INSTALL} DESTINATION "./imageformats/")
install(FILES		"${QT_PATH}/plugins/bearer/qgenericbearer.dll"  DESTINATION "./bearer/")
install(FILES		"${QT_PATH}/plugins/iconengines/qsvgicon.dll"  DESTINATION "./iconengines/")
install(FILES		"${QT_PATH}/plugins/platforms/qwindows.dll"  DESTINATION "./platforms/")
install(FILES		"${QT_PATH}/plugins/styles/qwindowsvistastyle.dll"  DESTINATION "./styles/")
install(DIRECTORY	"zlibrary/core/data/encodings" DESTINATION "./zlibrary/")
install(DIRECTORY	"zlibrary/core/data/resources" DESTINATION "./zlibrary/")
install(FILES		"zlibrary/core/data/languagePatterns.zip"  DESTINATION "./zlibrary/")
install(FILES		"zlibrary/core/data/unicode.xml.gz"  DESTINATION "./zlibrary/")
install(FILES		"zlibrary/text/data/hyphenationPatterns.zip"  DESTINATION "./zlibrary/")
install(FILES		"zlibrary/ui/data/keynames.desktop-qt4.xml"  DESTINATION "./zlibrary/" RENAME "keynames-qt4.xml")
install(FILES		"zlibrary/ui/data/style.desktop.qss"  DESTINATION "./zlibrary/" RENAME "style.qss")
file(GLOB BOOKTREE_RES "fbreader/data/icons/booktree/new/*")
install(FILES		 ${BOOKTREE_RES} DESTINATION "./icons/")
file(GLOB TOOLBAR_RES "fbreader/data/icons/toolbar/desktop/*")
install(FILES		 ${TOOLBAR_RES} DESTINATION "./icons/")
install(FILES		"fbreader/data/icons/application/64x64.png" DESTINATION "./icons/" RENAME "FBReader.png")
install(FILES		"fbreader/data/icons/back_button.png" DESTINATION "./icons/")
install(FILES		"fbreader/data/icons/forward_button.png" DESTINATION "./icons/")
install(FILES		"fbreader/data/icons/search_icon.png" DESTINATION "./icons/")
install(FILES		"fbreader/data/default/config.desktop.xml" DESTINATION "./FBReader/default/" RENAME "config.xml")
install(FILES		"fbreader/data/default/keymap.desktop.xml" DESTINATION "./FBReader/default/" RENAME "keymap.xml")
install(FILES		"fbreader/data/default/menubar.desktop.xml" DESTINATION "./FBReader/default/" RENAME "menubar.xml")
install(FILES		"fbreader/data/default/styles.desktop.xml" DESTINATION "./FBReader/default/" RENAME "styles.xml")
install(FILES		"fbreader/data/default/toolbar.desktop.xml" DESTINATION "./FBReader/default/" RENAME "toolbar.xml")
install(DIRECTORY	"fbreader/data/formats" DESTINATION "./FBReader/")
file(GLOB RESOURCES_RES "fbreader/data/resources/*.xml")
install(FILES		 ${RESOURCES_RES} DESTINATION "./FBReader/resources/")
set(CPACK_PACKAGE_NAME "FBReader")
set(CPACK_PACKAGE_VENDOR djdron)
file(STRINGS "fbreader/VERSION" VERSION_STR)
set(CPACK_PACKAGE_VERSION "${VERSION_STR}")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/fbreader/data/icons/application/FBReader.ico")
set(CPACK_WIX_PRODUCT_ICON ${CPACK_PACKAGE_ICON})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "FBReader")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "e-book reader")
set(CPACK_PACKAGE_FILE_NAME "FBReader_${CPACK_PACKAGE_VERSION}_win32_qt5")
set(CPACK_GENERATOR WIX)
set(CPACK_WIX_UPGRADE_GUID "AFD379EA-E866-4900-9293-01B4AC936072")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl-2.0.rtf")
include(CPack)
endif(WIN32)
