set(PROJECT_NAME zlui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(GLOB SRCS_CXX "src/qt4/time/*.cpp" "src/qt4/dialogs/*.cpp" "src/qt4/view/*.cpp" "src/qt4/image/*.cpp" "src/qt4/util/*.cpp" "src/qt4/filesystem/*.cpp" "src/qt4/library/*.cpp" "src/qt4/application/*.cpp" "src/qt4/network/*.cpp" "src/qt4/tree/*.cpp")
if(WIN32)
file(GLOB SRCS_CXX_PLATFORM "src/win32/message/*.cpp")
elseif(UNIX)
file(GLOB SRCS_CXX_PLATFORM "src/unix/message/*.cpp")
endif(WIN32)
LIST(APPEND SRCS_CXX ${SRCS_CXX_PLATFORM})

file(GLOB_RECURSE SRCS_H "src/qt4/*.h")

add_library(${PROJECT_NAME} STATIC ${SRCS_CXX} ${SRCS_H})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network zlcore zltext)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "zl")
