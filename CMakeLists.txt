#-------------------------------------------------------------------------------
#	CMAKE
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.7)

project(Tetris LANGUAGES CXX)

#-------------------------------------------------------------------------------
#	COMPILER
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ERROR_FLAGS "-Wall -Werror -Wextra -Wfatal-errors -pedantic-errors")
set(DEBUG_FLAGS "-g -ggdb")
set(RELEASE_FLAGS "-O2")

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS} ${ERROR_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${RELEASE_FLAGS}")

#-------------------------------------------------------------------------------
#	LIBRARIES
#-------------------------------------------------------------------------------

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#-------------------------------------------------------------------------------
#	EXECUTABLES
#-------------------------------------------------------------------------------

add_executable(Tetris
  src/board.cpp
  src/board.hpp
  src/colors.hpp
  src/game.cpp
  src/game.hpp
  src/gamepage.hpp
  src/ingame.cpp
  src/ingame.hpp
  src/main.cpp
  src/scoreviewer.cpp
  src/scoreviewer.hpp
  src/startgame.cpp
  src/startgame.hpp
  src/tetromino.cpp
  src/tetromino.hpp
)
target_link_libraries(Tetris ${SDL2_LIBRARIES} SDL2_ttf)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
