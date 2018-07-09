//
// Created by Eric Falk on 09.07.18.
//

#ifndef SEQUENCE_REVERSEBITREADER_H
#define SEQUENCE_REVERSEBITREADER_H


#include <cstdint>

class ReverseBitReader {

public:
    ReverseBitReader(uint8_t* buffer, uint32_t bufferSize);
    ~ReverseBitReader();

    int8_t getNextBit();

private:
    uint8_t* buffer;
    uint32_t bufferSize;
    int32_t position;

    uint8_t currentByte;
    uint8_t readFromByte;
};




#endif //SEQUENCE_REVERSEBITREADER_H
