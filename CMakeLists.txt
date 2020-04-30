cmake_minimum_required (VERSION 3.0.0)
project(Sudoku-Solver)

#use the c++ 14 standard
set(CMAKE_CXX_STANDARD 14)

#Bring the headers, such as game.h into the project
include_directories( includes )

#Find all cpp files
file(GLOB SOURCES "src/*.cpp")

#Building SeWorms
add_executable(Sudoku-Solver ${SOURCES})