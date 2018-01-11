set(CAD_INCLUDES_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/app/"
						"${CMAKE_CURRENT_SOURCE_DIR}/app/App.h"
						CACHE INTERNAL "App headers")

add_subdirectory(definitions)
add_subdirectory(ui)
add_subdirectory(data)
add_subdirectory(command)
add_subdirectory(app)