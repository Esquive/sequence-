//
// Created by Eric Falk on 10.07.18.
//

#ifndef SEQUENCE_BITINPUTSTREAM_H
#define SEQUENCE_BITINPUTSTREAM_H


#include <cstdint>

class BitInputStream {

private:

    uint32_t currentBufferPosition = 0;
    uint8_t currByte = 0;
    uint8_t bitsRead = 0;
    uint8_t *buffer;

public:
    BitInputStream(uint8_t *buffer);
    ~BitInputStream();

    void getNextBit();
    uint32_t getCurrentBufferPosition();
    void flush();


};


#endif //SEQUENCE_BITINPUTSTREAM_H
