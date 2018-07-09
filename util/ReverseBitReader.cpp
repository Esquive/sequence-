//
// Created by Eric Falk on 09.07.18.
//

#include "ReverseBitReader.h"

//1010 1010
//1111 0000
//0000 1111
//1000 1101
//uint8_t values[] = {170,240,15,141};
ReverseBitReader::ReverseBitReader(uint8_t* buffer, uint32_t bufferSize) {
    this->buffer = buffer;
    this->bufferSize = bufferSize;
    this->position = bufferSize - 1;

    this->readFromByte = 8;
}

int8_t ReverseBitReader::getNextBit() {
    if(readFromByte == 8){
        if(position >= 0) {
            this->currentByte = buffer[position];
            position--;
            readFromByte = 0;
        } else return -1;
    }

    int8_t returnValue = currentByte & 1;
    currentByte = currentByte >> 1;
    readFromByte++;
    return returnValue;
}
