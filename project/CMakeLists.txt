cmake_minimum_required(VERSION 2.8)

project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


find_package(SDL2)
if(SDL2_FOUND)
	MESSAGE('SDL2 FOUND')
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} third-party/glimac/include/ third-party/glm/ third-party/assimp/)
	set(ALL_LIBRARIES glimac ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} assimp)
else()
	find_package(SDL)
	MESSAGE('SDL2 NOT FOUND ; LOADING SDL1.2')
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} third-party/glimac/include/ third-party/glm/ third-party/assimp/)
	set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} assimp)
endif()


# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

add_subdirectory(third-party)
add_subdirectory(template)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})