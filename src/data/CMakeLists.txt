file (GLOB DATA "*.h" "*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/src/definitions")

add_library(data ${DATA})