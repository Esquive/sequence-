//
// Created by Eric Falk on 26.06.18.
//

#ifndef SEQUENCE_BITOUTPUTSTREAM_H
#define SEQUENCE_BITOUTPUTSTREAM_H


#include <cstdint>
#include <zconf.h>

class BitOutputStream {

private:

    uint32_t currentBufferPosition = 0;
    uint8_t currByte = 0;
    uint8_t bitsWritten = 0;
    uint8_t *buffer;

public:
    BitOutputStream(uint8_t *buffer);
    ~BitOutputStream();

    void writeBit(uint8_t bit);
    uint32_t getCurrentBufferPosition();
    void flush();
};


#endif //SEQUENCE_BITOUTPUTSTREAM_H
