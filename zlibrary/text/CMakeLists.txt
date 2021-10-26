set(PROJECT_NAME zltext)

file(GLOB SRCS_CXX "src/model/*.cpp" "src/area/*.cpp" "src/view/*.cpp" "src/style/*.cpp" "src/styleOptions/*.cpp" "src/hyphenation/*.cpp")
file(GLOB_RECURSE SRCS_H "*.h")

include_directories("include")

add_library(${PROJECT_NAME} STATIC ${SRCS_CXX} ${SRCS_H})
target_link_libraries(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "zl")
