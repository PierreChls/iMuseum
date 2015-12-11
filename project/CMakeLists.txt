cmake_minimum_required(VERSION 2.8)
project(iSeason)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


find_package(OpenGL REQUIRED)


add_subdirectory(third-party)
add_subdirectory(template)
