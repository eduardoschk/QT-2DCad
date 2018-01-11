set(CAD_SOURCES_FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/App.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")										
						
include_directories(${DEFINITION_FILES})
include_directories(${DATA_INCLUDES_FILES})
include_directories(${USER_INTERFACE_INCLUDES_FILES})
include_directories(${COMMAND_INCLUDES_FILES})

#############QT###############

find_package(Qt5Widgets CONFIG
        PATHS C:/Qt/5.9.2/msvc2017_64/lib/cmake/Qt5Widgets
        NO_DEFAULT_PATH)

###########ENDQT#############

add_executable(CAD ${CAD_INCLUDES_FILES} ${CAD_SOURCES_FILES} resources.qrc)
set_target_properties(CAD PROPERTIES ENABLE_EXPORTS 1)

target_link_libraries(CAD data)
target_link_libraries(CAD ui)
target_link_libraries(CAD command)
target_link_libraries(CAD Qt5::Core)

# add_custom_command(
	# TARGET CAD POST_BUILD
	# COMMAND ${CMAKE_COMMAND} -E copy
			# ${USER_INTERFACE_QT_DLLS_FILES}
			# ${CMAKE_CURRENT_BINARY_DIR}/Debug)
