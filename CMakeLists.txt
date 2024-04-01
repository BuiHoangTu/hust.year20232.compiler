cmake_minimum_required(VERSION 3.22)
project(InYear4_2_Compiler C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(minilib)
include_directories(minilib)

add_executable(prog main.c)
