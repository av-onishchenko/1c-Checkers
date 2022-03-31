cmake_minimum_required(VERSION 3.21)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

add_executable(checkers main.cpp Positions.cpp Positions.h Cell.cpp Cell.h  Checkers.cpp Checkers.h)
