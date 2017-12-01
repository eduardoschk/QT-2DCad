file (GLOB UI "*.h" "*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/src/app")
include_directories("${PROJECT_SOURCE_DIR}/src/data")
include_directories("${PROJECT_SOURCE_DIR}/src/definitions")

##############################
#############QT###############

find_package(Qt5Widgets CONFIG
        PATHS C:/Qt/5.9.2/msvc2017_64/lib/cmake/Qt5Widgets
        NO_DEFAULT_PATH)

list(APPEND THIRD_PARTY_LIBS Qt5::Widgets Qt5::Core)

###########ENDQT#############

add_library(ui STATIC ${UI})

target_link_libraries(ui Qt5::Widgets)
target_link_libraries(ui Qt5::Gui)