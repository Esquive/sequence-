cmake_minimum_required(VERSION 3.10)
project(sequence__)

set(CMAKE_CXX_STANDARD 11)

add_executable(sequence__ main.cpp
        encoding/FrequencyTable.h
        encoding/FrequencyTable.cpp
        encoding/TANSEncoder.cpp
        encoding/TANSEncoder.h
        io/FileOutput.cpp
        io/FileOutput.h
        io/BitOutputStream.cpp
        io/BitOutputStream.h
        util/ByteBuffer.h
        util/ByteBuffer.cpp
        util/ByteBuffer.h
        util/ByteBuffer.cpp
        util/ByteBuffer.h
        util/ByteBuffer.cpp
        util/ByteBuffer.h util/ReverseBitReader.cpp util/ReverseBitReader.h encoding/TANSDecoder.cpp encoding/TANSDecoder.h io/BitInputStream.cpp io/BitInputStream.h)