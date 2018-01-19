set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)

set(CAD_SOURCES_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/App.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")										
						
include_directories(${DEFINITION_INCLUDES_FILES})
include_directories(${DATA_INCLUDES_FILES})
include_directories(${USER_INTERFACE_INCLUDES_FILES})
include_directories(${COMMAND_INCLUDES_FILES})

add_executable(CAD ${CAD_INCLUDES_FILES} ${CAD_SOURCES_FILES} resources.qrc)
set_target_properties(CAD PROPERTIES ENABLE_EXPORTS 1)

target_link_libraries(CAD data)
target_link_libraries(CAD ui)
target_link_libraries(CAD command)
target_link_libraries(CAD definitions)
target_link_libraries(CAD Qt5::Core)

