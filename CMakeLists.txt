cmake_minimum_required(VERSION 3.15)

project(Tetris)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/raylib)

add_executable(Tetris
    src/main.cpp
    src/Tetromino.cpp
    src/Game.cpp
)

target_link_libraries(Tetris PRIVATE raylib)