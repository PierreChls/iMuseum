cmake_minimum_required(VERSION 2.8)
project(iSeason)

find_package(OpenGL REQUIRED)
message(${OPENGL_INCLUDE_DIR})


add_subdirectory(third-party)
add_subdirectory(template)
