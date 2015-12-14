cmake_minimum_required(VERSION 2.8)
project(iSeason)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

#FOR MAC
find_package(SDL2)
if(SDL2_FOUND)
include_directories(${SDL_INCLUDE_DIR})
MESSAGE("SDL2 FOUND")
else()
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
MESSAGE("SDL2 NOT FOUND, LOADING SDL1.2")
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

#FOR UNIVERSITY
	#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)



include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} third-party/glimac/include third-party/glm third-party/assimp/include/)


set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} assimp)


add_subdirectory(third-party)
add_subdirectory(template)


file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})