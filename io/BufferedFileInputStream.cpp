//
// Created by Eric Falk on 14.07.18.
//

#include <string>
#include <unistd.h>
#include "BufferedFileInputStream.h"

BufferedFileInputStream::BufferedFileInputStream(const std::string &srcFile, uint32_t bufferSize) {
    if(access( fname, F_OK ) != -1) {
        this->buffer = new uint8_t[bufferSize];
        this->capacity = bufferSize;
        this->position = 0;
    } else {

    }
}

BufferedFileInputStream::~BufferedFileInputStream() {
    delete [] this->buffer;
}

int16_t BufferedFileInputStream::get() {
    if(hasRemaining(1)){
        return (int16_t )buffer[position++];
    }
    return -1;
}

uint8_t *BufferedFileInputStream::getSlice(uint32_t begin) {
    if(begin<capacity){
        return &buffer[begin];
    }
    return nullptr;
}

bool BufferedFileInputStream::hasRemaining(uint32_t number){
    return (position + number) < capacity;
}

