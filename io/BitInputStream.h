//
// Created by Eric Falk on 10.07.18.
//

#ifndef SEQUENCE_BITINPUTSTREAM_H
#define SEQUENCE_BITINPUTSTREAM_H


#include <cstdint>

class BitInputStream {

private:

    uint32_t currentBufferPosition = 0;
    uint32_t bufferSize;
    uint8_t currByte = 0;
    uint8_t bitsRemaining = 8;
    uint8_t *buffer;

    bool hasRemaining();

public:
    BitInputStream(uint8_t *buffer, uint32_t bufferSize);
    ~BitInputStream();

    int8_t getNextBit();
    uint32_t getCurrentBufferPosition();
};


#endif //SEQUENCE_BITINPUTSTREAM_H
