file (GLOB COMMAND "*.h" "*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/src/ui")
include_directories("${PROJECT_SOURCE_DIR}/src/data")
include_directories("${PROJECT_SOURCE_DIR}/src/definitions")

add_library(command ${COMMAND})

target_link_libraries(command data)
target_link_libraries(command ui)