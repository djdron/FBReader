set(PROJECT_NAME zlcore)

file(GLOB SRCS_CXX
	"src/library/*.cpp" "src/typeId/*.cpp" "src/util/*.cpp" "src/constants/*.cpp" "src/logger/*.cpp" "src/filesystem/*.cpp" "src/filesystem/zip/*.cpp"
	"src/filesystem/bzip2/*.cpp" "src/filesystem/tar/*.cpp" "src/dialogs/*.cpp" "src/optionEntries/*.cpp" "src/application/*.cpp" "src/view/*.cpp"
	"src/encoding/*.cpp" "src/options/*.cpp" "src/message/*.cpp" "src/resources/*.cpp" "src/time/*.cpp" "src/xml/*.cpp" "src/xml/expat/*.cpp"
	"src/image/*.cpp" "src/language/*.cpp" "src/unix/time/*.cpp" "src/runnable/*.cpp" "src/network/*.cpp" "src/network/requests/*.cpp" "src/blockTreeView/*.cpp"
	"src/tree/*.cpp"
	"src/unix/xmlconfig/*.cpp"
)

if(WIN32)
file(GLOB PLATFORM_SRCS_CXX "src/desktop/dialogs/*.cpp" "src/win32/encoding/*.cpp" "src/win32/filesystem/*.cpp" "src/win32/config/*.cpp" "src/win32/library/*.cpp")
elseif(UNIX)
file(GLOB PLATFORM_SRCS_CXX "src/unix/filesystem/*.cpp" "src/unix/iconv/*.cpp" "src/unix/library/*.cpp")
endif(WIN32)

list(APPEND SRCS_CXX ${PLATFORM_SRCS_CXX})

file(GLOB_RECURSE SRCS_H "*.h")

include_directories("include")

add_library(${PROJECT_NAME} STATIC ${SRCS_CXX} ${SRCS_H})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "zl")
