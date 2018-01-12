set(COMMAND_INCLUDES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/"
						   "${CMAKE_CURRENT_SOURCE_DIR}/Command.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateArc.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateLine.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateBezier.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateDraw.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateNewFile.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandIOFile.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandOpenFile.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandResizeWindow.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandSaveAsFile.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandSaveFile.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandZoomValueChange.h"
						   "${CMAKE_CURRENT_SOURCE_DIR}/CommandMoveScroll.h"
						   CACHE INTERNAL "Commmand includes files")
						
set(COMMAND_SOURCES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateArc.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateLine.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateBezier.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateDraw.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandCreateNewFile.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandIOFile.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandOpenFile.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandResizeWindow.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandSaveAsFile.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandSaveFile.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandZoomValueChange.cpp"
						  "${CMAKE_CURRENT_SOURCE_DIR}/CommandMoveScroll.cpp")
						  
include_directories(${DEFINITION_FILES})
include_directories(${USER_INTERFACE_INCLUDES_FILES})
include_directories(${DATA_INCLUDES_FILES})

add_library(command ${COMMAND_INCLUDES_FILES} ${COMMAND_SOURCES_FILES})

target_link_libraries(command ui)