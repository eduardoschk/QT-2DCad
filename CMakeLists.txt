cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installDir")

project(CAD)

include(qt5)

add_subdirectory(src)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)