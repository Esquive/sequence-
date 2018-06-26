//
// Created by Eric Falk on 26.06.18.
//

#include "../headers/ByteBuffer.h"

ByteBuffer::ByteBuffer(uint32_t bufferSize) {
    buffer = new uint8_t[bufferSize];
}

ByteBuffer::~ByteBuffer() {
    delete[] buffer;
}
