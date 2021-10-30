set(PROJECT_NAME fbreader)

file(GLOB SRCS_CXX
	"src/database/*.cpp" "src/database/sqldb/*.cpp" "src/database/sqldb/implsqlite/*.cpp" "src/database/booksdb/*.cpp" "src/database/booksdb/runnables/*.cpp"
	"src/database/networkdb/*.cpp" "src/database/networkdb/runnables/*.cpp" "src/migration/*.cpp" "src/options/*.cpp" "src/library/*.cpp" "src/bookmodel/*.cpp"
	"src/formats/*.cpp" "src/formats/fb2/*.cpp" "src/formats/css/*.cpp" "src/formats/html/*.cpp" "src/formats/pdb/*.cpp" "src/formats/txt/*.cpp"
	"src/formats/tcr/*.cpp" "src/formats/chm/*.cpp" "src/formats/xhtml/*.cpp" "src/formats/oeb/*.cpp" "src/formats/rtf/*.cpp" "src/formats/openreader/*.cpp"
	"src/formats/doc/*.cpp" "src/formats/util/*.cpp" "src/external/*.cpp" "src/fbreader/*.cpp" "src/encodingOption/*.cpp" "src/network/*.cpp"
	"src/network/authentication/*.cpp" "src/network/atom/*.cpp" "src/network/opds/*.cpp" "src/network/litres/*.cpp" "src/network/tree/*.cpp"
	"src/network/authentication/litres/*.cpp" "src/blockTree/*.cpp" "src/libraryActions/*.cpp" "src/libraryTree/*.cpp" "src/networkActions/*.cpp"
	"src/tree/*.cpp" "src/optionsDialog/*.cpp"
)
file(GLOB_RECURSE SRCS_H "src/*.h")
if(WIN32)
file(GLOB RES_RC "win32/fbreader.rc")
endif(WIN32)

file(STRINGS "VERSION" VERSION_STR)
add_definitions(-DVERSION="${VERSION_STR}")

add_executable(${PROJECT_NAME} WIN32 ${SRCS_CXX} ${SRCS_H} ${RES_RC})
