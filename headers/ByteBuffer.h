//
// Created by Eric Falk on 26.06.18.
//

#ifndef SEQUENCE_BYTEBUFFER_H
#define SEQUENCE_BYTEBUFFER_H


#include <cstdint>

class ByteBuffer {
private:
    uint32_t bufferSize;
    uint8_t* buffer;

    uint32_t capacity;
    uint32_t position = 0;

public:
    ByteBuffer(uint32_t bufferSize);
    ~ByteBuffer();
};


#endif //SEQUENCE_BYTEBUFFER_H
