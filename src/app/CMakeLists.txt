file(GLOB SOURCE_FILES "*.cpp" "*.h")

include_directories("${PROJECT_SOURCE_DIR}/src/ui")
include_directories("${PROJECT_SOURCE_DIR}/src/data")
include_directories("${PROJECT_SOURCE_DIR}/src/command")

##############################
#############QT###############

find_package(Qt5Widgets CONFIG
        PATHS C:/Qt/5.9.2/msvc2017_64/lib/cmake/Qt5Widgets
        NO_DEFAULT_PATH)

list(APPEND THIRD_PARTY_LIBS Qt5::Widgets Qt5::Core)

###########ENDQT#############

add_executable(CAD ${SOURCE_FILES})
set_target_properties(CAD PROPERTIES ENABLE_EXPORTS 1)

target_link_libraries(CAD data)
target_link_libraries(CAD ui)
target_link_libraries(CAD command)
target_link_libraries(CAD Qt5::Core)
