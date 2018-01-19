if(__QT5_INCLUDED)
  return()
endif()
set(__QT5_INCLUDED TRUE)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set_target_properties(Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WinMain PROPERTIES 
MAP_IMPORTED_CONFIG_DEBUGIPP "DEBUG"
MAP_IMPORTED_CONFIG_RELEASEIPP "RELEASE")
