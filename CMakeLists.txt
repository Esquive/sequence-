cmake_minimum_required(VERSION 3.10)
project(sequence__)

set(CMAKE_CXX_STANDARD 11)

add_executable(sequence__ source/main.cpp headers/FrequencyTable.h source/FrequencyTable.cpp source/TANSEncoder.cpp headers/TANSEncoder.h source/FileOutput.cpp headers/FileOutput.h source/BitOutputStream.cpp headers/BitOutputStream.h headers/ByteBuffer.h source/ByteBuffer.cpp headers/ByteBuffer.h source/ByteBuffer.cpp headers/ByteBuffer.h source/ByteBuffer.cpp headers/ByteBuffer.h)