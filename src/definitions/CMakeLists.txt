set(DEFINITION_INCLUDES_FILES "${CMAKE_CURRENT_SOURCE_DIR}"
							 "${CMAKE_CURRENT_SOURCE_DIR}/ShapeTypes.h"
							 "${CMAKE_CURRENT_SOURCE_DIR}/Coordinate.h"
							 "${CMAKE_CURRENT_SOURCE_DIR}/Rect.h"
							 "${CMAKE_CURRENT_SOURCE_DIR}/Size.h"
							 "${CMAKE_CURRENT_SOURCE_DIR}/ZoomControl.h" CACHE INTERNAL "drawing files")	 
				
set(DEFINITION_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Rect.cpp"
							"${CMAKE_CURRENT_SOURCE_DIR}/Size.cpp"
							"${CMAKE_CURRENT_SOURCE_DIR}/Coordinate.cpp")				
				
add_library(definitions ${DEFINITION_INCLUDES_FILES} ${DEFINITION_SOURCE_FILES} )			
				
source_group("definitions" FILES "${DEFINITION_FILES}")