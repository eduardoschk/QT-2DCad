set(DATA_INCLUDES_FILES "${CMAKE_CURRENT_SOURCE_DIR}"
						"${CMAKE_CURRENT_SOURCE_DIR}/ArcShape.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/BezierShape.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Data.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Point.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Rect.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/DataViewController.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/File.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/IOFile.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/LineShape.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Shape.h"
						"${CMAKE_CURRENT_SOURCE_DIR}/Size.h"
						CACHE INTERNAL "Data includes files")
						
set(DATA_SOURCES_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/ArcShape.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/BezierShape.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/Data.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/DataViewController.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/File.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/IOFile.cpp"
						"${CMAKE_CURRENT_SOURCE_DIR}/LineShape.cpp")

include_directories(${DEFINITION_FILES})

add_library(data ${DATA_INCLUDES_FILES} ${DATA_SOURCES_FILES})