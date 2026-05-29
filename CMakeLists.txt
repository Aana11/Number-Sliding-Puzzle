cmake_minimum_required(VERSION 3.10)
project(shuzi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shuzi
    src/main.cpp
    src/puzzle_board.cpp
    src/solver.cpp
)

target_include_directories(shuzi PRIVATE ${CMAKE_SOURCE_DIR}/include)