set(USER_INTERFACE_INCLUDES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/"
								  "${CMAKE_CURRENT_SOURCE_DIR}/DrawArea.h"
								  "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h"
								  "${CMAKE_CURRENT_SOURCE_DIR}/NewDrawPopup.h"
								  "${CMAKE_CURRENT_SOURCE_DIR}/NewFileStructure.h"
								  "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface.h"
								  CACHE INTERNAL "USER INTERFACE INCLUDE HEADERS")
				
set(USER_INTERFACE_SOURCES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/DrawArea.cpp"
								 "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp"
								 "${CMAKE_CURRENT_SOURCE_DIR}/NewDrawPopup.cpp"
								 "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface.cpp")

set(USER_INTERFACE_QT_DLLS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dll/Qt5Cored.dll" 
								 "${CMAKE_CURRENT_SOURCE_DIR}/dll/Qt5Guid.dll"
								 "${CMAKE_CURRENT_SOURCE_DIR}/dll/Qt5Widgetsd.dll"
								 CACHE INTERNAL "User interface DLLS")						

include_directories(${DEFINITION_FILES})								  
include_directories(${CAD_INCLUDES_FILES})
include_directories(${DATA_INCLUDES_FILES})

#############QT###############

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG
        PATHS C:/Qt/5.9.2/msvc2017_64/lib/cmake/Qt5Widgets
        NO_DEFAULT_PATH)

list(APPEND THIRD_PARTY_LIBS Qt5::Widgets Qt5::Core)

###########ENDQT#############

add_library(ui STATIC ${USER_INTERFACE_INCLUDES_FILES} ${USER_INTERFACE_SOURCES_FILES})

target_link_libraries(ui Qt5::Widgets)
target_link_libraries(ui Qt5::Gui)