include_directories(include/)
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.hpp)

add_executable(game ${SRC_FILES} game.cpp)
message("all_libraries = " assimp)
target_link_libraries(game assimp )
