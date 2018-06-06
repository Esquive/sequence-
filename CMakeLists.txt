cmake_minimum_required(VERSION 3.10)
project(sequence__)

set(CMAKE_CXX_STANDARD 11)

add_executable(sequence__ source/main.cpp headers/fileio.h headers/FrequencyTable.h source/FrequencyTable.cpp)