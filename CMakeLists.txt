cmake_minimum_required(VERSION 3.8)

project(CAD)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)